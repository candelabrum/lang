#include "lex.hpp"
#include "str.hpp"
#include "l.hpp"
#include "edges.hpp"

bool IsLetter(char s)
{
	return (s == '_' || ('a' <= s && s <= 'z') || ('A' <= s && s <= 'Z'));
}

bool IsDelimiter(char symbol) 
{
	return 1 + str_delimiters.find_symbol(symbol);
}

bool IsWhiteSpace(char symbol)
{
	return (symbol == ' ' || symbol == '\n' || symbol == '\t');
}

bool IsNumber(char symbol)
{
	return (symbol >= '0' && symbol <= '9');
}

class Home_to_Home : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) 
	{
		return IsWhiteSpace(sym) || IsDelimiter(sym) || sym == '@';
	}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		if (IsDelimiter(sym))
		{
			c_l.prepare(sym, lex_undefined);
			c_l.type = TableDelimiters.search_by(c_l.lex);
			lst.add_node_to_end(c_l);
			c_l.reset();
		}
		/*else if (sym == '@')
			lst.add_node_to_end(c_l);*/
	}
}hhr, *hh = &hhr;

class Home_to_Error : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) { return 1; }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		printf("Line number : %d\n", c_l.number_line);
		printf("Error: The symbol does not belong to the alphabet\n");
		printf("%c\n", sym);
	}
}her, *he = &her;

class Home_to_Whole : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) { return IsNumber(sym); }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.reset();
		c_l.add_symbol(sym);
	}
}hwr, *hw = &hwr;

class Home_to_Identificator : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) { return sym == '$' || sym == '?';}
	void transition(char s, lexeme& c_l, list<lexeme>& lst)
	{
		s == '$'? c_l.prepare(s, lex_var) : c_l.prepare(s, lex_func);
	}
}hir, *hi = &hir;

class Home_to_BooleanExpression : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) { return  sym == '<' || sym == '>' ;}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.reset();
		c_l.add_symbol(sym);
	}
}hbr, *hb = &hbr;

class Home_to_Assignment : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) { return sym == ':'; }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.reset();
		c_l.add_symbol(sym);
	}
}har, *ha = &har;

class Home_to_LiteralString : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) { return sym == '"'; }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.reset();
		c_l.add_symbol(sym);
	}
}hlr, *hl = &hlr;

class Home_to_Comment : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) { return sym == '#'; }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.reset();
		c_l.add_symbol(sym);
	}
}hcr, *hc = &hcr;

class Home_to_Service : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) { return IsLetter(sym); }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.reset();
		c_l.add_symbol(sym);
	}
}hsr, *hs = &hsr;

class Whole_to_Whole : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) { return IsNumber(sym); }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.add_symbol(sym);
	}
}wwr, *ww = &wwr;

class Whole_to_Dot : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) { return sym == '.'; }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.add_symbol(sym);
	}
}wdr, *wd = &wdr;

class Whole_to_Home : public Edge
{
public:
	bool condition(char sym, lexeme& c_l)
	{
		return IsWhiteSpace(sym) || IsDelimiter(sym) || IsLetter(sym) || sym == '@';
	}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.type = lex_integ;
		lst.add_node_to_end(c_l);
		c_l.reset();
/*		c_l.set(current_line, undefined); !!! */
	}
	bool IsDelay(char sym) { return !IsWhiteSpace(sym); }
}whr, *wh = &whr;

class Whole_to_Error : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) {return 1;}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		printf("Line number : %d\n", c_l.number_line);
		printf("Error: Unexpected character in number\n");
		c_l.lex.print();
	}
}wer, *we = &wer;

class Dot_to_Fractional : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) { return IsNumber(sym); }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.add_symbol(sym);	
	}
}dfr, *df = &dfr;

class Dot_to_Error : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) {return 1;}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		printf("Line number : %d\n", c_l.number_line);
		if (sym != '@')
			printf("Error: Expected digit after dot\n");
		else 
			printf("Error: Unexpected end of file \n");
		c_l.lex.print();
	}
}der, *de = &der;

class Fract_to_Home  : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) 
	{ 
		return IsWhiteSpace(sym) || IsDelimiter(sym) ||
			IsLetter(sym) || sym == '@'; 
	}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.type = lex_fractional;
		lst.add_node_to_end(c_l);
		c_l.reset();
	}
	bool IsDelay(char sym) { return !IsWhiteSpace(sym); }
}fhr, *fh = &fhr;

class Fract_to_Fract  : public Edge
{
public:
	bool condition(char sym, lexeme& c_l){ return IsNumber(sym); }  
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.add_symbol(sym);
	}
}ffr, *ff = &ffr;

class Fract_to_Error  : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) {return 1;}  
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		printf("Line number : %d\n", c_l.number_line);
		printf("Error: This character can't be after a fractional ");
		c_l.lex.print();
	}
}fer, *fe = &fer;

class Identificator_to_Home  : public Edge
{
public:
	bool condition(char sym, lexeme& c_l)
	{
		return IsWhiteSpace(sym) || IsDelimiter(sym) ||
			sym == '@' || sym == ':';
	}  
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		lst.add_node_to_end(c_l);
		c_l.reset();
	}
	bool IsDelay(char sym) 
	{ 
		return !IsWhiteSpace(sym); 
	}
}ihr, *ih = &ihr;

class Identificator_to_Identificator  : public Edge
{
public:
	bool condition(char sym, lexeme& c_l)
	{
		return IsLetter(sym) || IsNumber(sym);
	}  
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.add_symbol(sym);
	}
}iir, *ii = &iir;

class Identificator_to_Error  : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) {return 1;}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		printf("Line number : %d\n", c_l.number_line);
		printf("Error: This character can't be found in the identifier\n");
		c_l.add_symbol(sym);
		c_l.lex.print();
	}
}ier, *ie = &ier;

class Comment_to_Home  : public Edge
{
public:
	bool condition(char sym, lexeme& c_l)
	{ 
		return sym == '\n' || sym == '@';
	}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.add_symbol(sym);
		c_l.type = lex_com; 
		lst.add_node_to_end(c_l);
		c_l.reset();
	}
}chr, *ch = &chr;

class Comment_to_Comment : public Edge
{
public:
	bool condition(char sym, lexeme& c_l)
	{ 
		return sym != '\n' && sym != '@';
	}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.add_symbol(sym);
	}
}ccr, *cc = &ccr;

class Comment_to_Error : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) {return 1;}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		printf("Line number : %d\n", c_l.number_line);
		printf("Error: Unexpected end of file in the comment token\n");
		c_l.lex.print();
	}
}cer, *ce = &cer;

class LiteralString_to_Home : public Edge
{
public:
	bool condition(char sym, lexeme& c_l){ return sym == '"'; }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.add_symbol(sym);
		c_l.type = lex_strlit;
		lst.add_node_to_end(c_l);
		c_l.reset();
	}
}lhr, *lh = &lhr;

class LiteralString_to_LiteralString : public Edge
{
public:
	bool condition(char sym, lexeme& c_l)
	{ 
		return sym != '"' && sym != '@'; 
	}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.add_symbol(sym);		
	}
}llr, *ll = &llr;

class LiteralString_to_Error : public Edge
{	
public:
	bool condition(char sym, lexeme& c_l){ return sym == '@'; }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		printf("Line number : %d\n", c_l.number_line);
		printf("Error: Unexpected end of file \n");
		c_l.lex.print();
	}
}ler, *le = &ler;

class Assignment_to_Home : public Edge
{
public:
	bool condition(char sym, lexeme& c_l){ return sym == '='; }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.add_symbol(sym);
		c_l.type = TableDelimiters.search_by(c_l.lex);
		lst.add_node_to_end(c_l);
		c_l.reset();
	}
}ahr, *ah = &ahr;

class Assignment_to_Error : public Edge
{
public:
	bool condition(char sym, lexeme& c_l){ return sym != '='; }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		printf("Line number : %d\n", c_l.number_line);
		c_l.add_symbol(sym);
		printf("Expected character = \n");
		c_l.lex.print();
	}
}aer, *ae = &aer;

class ServiceWord_to_Home : public Edge
{
public:
	bool condition(char s, lexeme& c_l)
	{
		return (IsWhiteSpace(s) || IsDelimiter(s) || s == '@') && 
			TableKeyWords.search_by(c_l.lex) != lex_null;
	}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.type = TableKeyWords.search_by(c_l.lex);
		lst.add_node_to_end(c_l);
		c_l.reset();
	}
	bool IsDelay(char sym) { return !IsWhiteSpace(sym); }
}shr, *sh = &shr;

class ServiceWord_to_ServiceWord : public Edge
{
public:
	bool condition(char sym, lexeme& c_l){ return IsLetter(sym); }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		c_l.add_symbol(sym);
	}
}ssh, *ss = &ssh;

class ServiceWord_to_Error : public Edge
{
public:
	bool condition(char sym, lexeme& c_l){ return 1; /* like else */ }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		printf("Line number : %d\n", c_l.number_line);
		printf("Error: Expected service word\n");
		c_l.lex.print();
	}
}ser, *se = &ser;

/*maybe bad work because IsDelay and condition maybe bad */
class BooleanExpression_to_Home : public Edge 
{
/*was    bood IsCoditionForDelay(char sym)
	{
		return (IsWhiteSpace(sym) || IsNumber(sym) ||
		IsLetter(sym) || IsDelimiter(sym) ||
		symbol == '@' || sym == ':') && sym != '='; 
	} */
public:
	bool condition(char sym, lexeme& c_l) { return 1; }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		if (sym == '=')
			c_l.add_symbol(sym);
		c_l.type = TableDelimiters.search_by(c_l.lex);
		lst.add_node_to_end(c_l);
		c_l.reset();
	}
	bool IsDelay(char sym) { return sym != '='; }
}bhr, *bh = &bhr;

class BooleanExpression_to_Error : public Edge
{
public:
    bool condition(char sym, lexeme& c_l){ return 1; }
	void transition(char sym, lexeme& c_l, list<lexeme>& lst)
	{
		printf("Line number : %d\n", c_l.number_line);
		printf("This will never happen\n");	
	}
}ber, *be = &ber;

class Error_to_Error : public Edge
{
public:
	bool condition(char sym, lexeme& c_l) {return 1;}
	void transition(char sym, lexeme& c_l, list<lexeme>& lst){}
}eer, *ee = &eer;

int	const size = 11;

Edge *AdjMatrix[size][size] = {
/*			 1   2   3   4   5   6   7   8   9   10  11 */
/* home  */	{hh, hw, 0 , 0 , hi, hc, hl, ha, hs, hb, he },
/* whole */ {wh, ww, wd, 0 , 0 , 0 , 0 , 0 , 0 , 0 , we },
/* dot   */ {0 , 0 , 0 , df, 0 , 0 , 0 , 0 , 0 , 0 , de },
/* fract */ {fh, 0 , 0 , ff, 0 , 0 , 0 , 0 , 0 , 0 , fe },
/* ident */ {ih, 0 , 0 , 0 , ii, 0 , 0 , 0 , 0 , 0 , ie },
/* comm  */ {ch, 0 , 0 , 0 , 0 , cc, 0 , 0 , 0 , 0 , ce },
/* lstr  */ {lh, 0 , 0 , 0 , 0 , 0 , ll, 0 , 0 , 0 , le },
/* assig */ {ah, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , ae },
/* serv  */ {sh, 0 , 0 , 0 , 0 , 0 , 0 , 0 , ss, 0 , se },
/* boole */ {bh, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , be },
/* error */ {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , ee },
};



