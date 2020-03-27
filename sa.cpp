#include <stdio.h>
#include <stdlib.h>
#include "lex.hpp"
#include "l.hpp"
#include "sa.hpp"

/*StatGmSt is a bad name */ 
/*Alphabet of terminal characters*/
/* Make first for all NonTerminal Symbols and check this in if */
/* Maybe if->if(
	Duplicate code in functions: ProcName0, ArgsName1, ArgsName2 
*/

void SyntaxAnalyzer::Start(list<lexeme> &a_lst)
{
	lst = a_lst; 
	a_lst.make_null();
	get_lex();
	StatList();
	ProcessTermSym(lex_fin, "Expected end of file. "
								"Probably you don't write ;\n");
	printf("\nAlready done\n");
}

void SyntaxAnalyzer::GoodBye(const char *str)
{
	printf("%s", str);
	c_l.print();
	exit(1);
}

void SyntaxAnalyzer::get_lex()
{
	lexeme *tmp;

	tmp = &lst.get_data(0);
	while(tmp && tmp->type == lex_com)
	{
		lst.next();
		tmp = &lst.get_data(0);
	}
	if (tmp)
		c_l = *tmp;
	lst.next();
} 

void SyntaxAnalyzer::ProcessTermSym(type_lexeme t, const char *msg)
{
	if (c_l.type != t)
		GoodBye(msg);
	get_lex();
}

void SyntaxAnalyzer::DeleteAllComments()
{
	lst.delete_nodes(lex_com);
}

void SyntaxAnalyzer::Var()
{
	printf("Var-->");
	ProcessTermSym(lex_var, "Expected variable\n");
	VarAux();
}

void SyntaxAnalyzer::VarAux()
{
	printf("VarAux-->");
	if (c_l.type == lex_open_sq_br)
	{
		get_lex();
		ArExpr();
		ProcessTermSym(lex_close_sq_br, "After variable: Expected ]\n");
	}
}

bool SyntaxAnalyzer::BelongToFirstArExpr(type_lexeme t)
{
	/* make a normal array of type_lexeme */
	return c_l.type == lex_var || c_l.type == lex_integ ||
		c_l.type == lex_fractional || c_l.type == lex_func_one ||
		c_l.type == lex_func_zero || c_l.type == lex_open_bracket;
}

void SyntaxAnalyzer::ArExpr()
{
	printf("ArExpr1-->");
	if (!BelongToFirstArExpr(c_l.type))
		GoodBye("Expected Arithmetic Expression with + and -\n");
	ArExpr1();
	while(c_l.type == lex_plus || c_l.type == lex_minus)
	{
		get_lex();
		ArExpr1();
	}
}

void SyntaxAnalyzer::ArExpr1()
{
	printf("ArExpr1-->");
	if (!BelongToFirstArExpr(c_l.type))
		GoodBye("Expected Arithmetic Expression with * and /\n");
	ArExpr2();
	while(c_l.type == lex_star || c_l.type == lex_slash)
	{
		get_lex();
		ArExpr2();
	}
}

void SyntaxAnalyzer::ArExpr2()
{
	printf("ArExpr2-->");
	/* make a switch  or maybe not*/
	if (c_l.type == lex_var)
	{
		Var();
	}
	else
	if (c_l.type == lex_func_one || c_l.type == lex_func_zero)
	{
		Function();
	}
	else
	if (c_l.type == lex_open_bracket)
	{
		get_lex();
		ArExpr();
		if (c_l.type != lex_close_bracket)
			GoodBye("Arithmetic Expression:Expected ) ");
	}
	else 
	if (c_l.type == lex_integ || c_l.type == lex_fractional)
	{
		get_lex();	
	}
	else
		GoodBye("Arithmetic Expression: Unexpected lexeme\n");
}

bool SyntaxAnalyzer::IsCmpSign(type_lexeme t)
{
	return t == lex_equality || t == lex_lss ||
		t == lex_gtr || t == lex_leq || t == lex_geq;
}

bool SyntaxAnalyzer::BelongToFirstBoolExpr(type_lexeme t)
{
	return t == lex_integ || t == lex_fractional||
		t == lex_var || t == lex_open_bracket || t == lex_neg ||
		t == lex_func_zero || t == lex_func_one;
}


void SyntaxAnalyzer::BoolExpr()
{
	printf("BoolExpr-->");
	if (!BelongToFirstBoolExpr(c_l.type))
		GoodBye("Expected Boolean Expression probably with <, > etc\n");
	BoolExpr1();
	if (IsCmpSign(c_l.type))
	{
		get_lex();
		BoolExpr1();
	}
}

void SyntaxAnalyzer::BoolExpr1()
{
	printf("BoolExpr1-->");
	if (!BelongToFirstBoolExpr(c_l.type))
		GoodBye("Expected Boolean Expression probably with |\n");
	BoolExpr2();
	while(c_l.type == lex_or)
	{
		get_lex();
		BoolExpr2();
	}
}

void SyntaxAnalyzer::BoolExpr2()
{
	printf("BoolExpr2-->");
	if (!BelongToFirstBoolExpr(c_l.type))
		GoodBye("Expected Boolean Expression probably with |\n");
	BoolExpr3();
	while(c_l.type == lex_and)
	{
		get_lex();
		BoolExpr3();
	}
}

void SyntaxAnalyzer::BoolExpr3()
{
	printf("BoolExpr3-->");
	switch(c_l.type)
	{
	case lex_var:
		Var();
		break;
	case lex_func_one:
	case lex_func_zero:
		Function();
		break;
	case lex_open_bracket:
		get_lex();
		ArExpr();
		if (c_l.type != lex_close_bracket)
			GoodBye("BoolExpression: Expected ) ");
		break;
	case lex_integ: 
	case lex_fractional:
		get_lex();	
		break;
	case lex_neg:
		get_lex();
		BoolExpr3();
		break;
	default:
		GoodBye("BoolExpression: Unexpected lexeme\n");
	}
}

void SyntaxAnalyzer::ArgsFunc0()
{
	printf("ArgsFunc0-->");
	ProcessTermSym(lex_open_bracket, "Function: Expected (\n");
	ProcessTermSym(lex_close_bracket, "Function: Expected )\n");
}

void SyntaxAnalyzer::ArgsFunc1()
{
//	get_lex();
	printf("ArgsFunc1-->");
	ProcessTermSym(lex_open_bracket, "Function: Expected (\n");
	ArExpr();
	ProcessTermSym(lex_close_bracket, "Funcstion: Expected )\n");
}

void SyntaxAnalyzer::Function()
{
	printf("Function-->");
	/* make a switch or maybe not*/
	if (c_l.type == lex_func_zero)
	{
		get_lex();
		ArgsFunc0();		
	}
	else 
	if (c_l.type == lex_func_one)
	{
		get_lex();
		ArgsFunc1();	
	}
	else
		GoodBye("It is not Name Function, but expected name Function \n");
}

void SyntaxAnalyzer::StatComp()
{
	printf("StatComp-->");
	ProcessTermSym(lex_curly_open_br, "Statement Compound: Expected {\n");
    StatList();	
	ProcessTermSym(lex_curly_close_br, "Statement Compound: Expected }\n");
}

bool SyntaxAnalyzer::BelongToFirstStatement(type_lexeme t)
{
	return t == lex_var || t == lex_if || t == lex_while ||
		t == lex_curly_open_br || t == lex_print || 
		t == lex_end_turn || t == lex_prod || t == lex_build ||
		t == lex_buy || t == lex_sell;
}

void SyntaxAnalyzer::StatList()
{
	if (!BelongToFirstStatement(c_l.type))
		GoodBye("Program must start with Statement or Compound Statement must contains Statements: Expected Statement \n");
	Statement();
	while(c_l.type == lex_semicolon)
	{
		get_lex();
		Statement();
	}
	printf("StatList was end\n");
}

void SyntaxAnalyzer::Statement()
{
	switch(c_l.type)
	{
	case lex_var:
		StatAssign();
		break;
	case lex_if:
		StatIf();
		break;
	case lex_print:
		StatPrint();
		break;
	case lex_while:
		StatWhile();
		break;
	case lex_end_turn:
	case lex_prod:
	case lex_build:
	case lex_buy:
	case lex_sell:
		StatGmSt();
		break;
	case lex_curly_open_br:
		StatComp();
		break;
	default:/*Maybe make first for begin and prepare probably error*/
		GoodBye("Expected Statement, but this is not statement\n");
	}
}

void SyntaxAnalyzer::StatAssign()
{
	/* condition was check */
	printf("StatAssign-->");
	if (c_l.type !=lex_var)
		GoodBye("StatAssignment : Expected Variable\n");
	Var();
	ProcessTermSym(lex_assignment, "Statement Assignment: Expected :=\n");
	ArExpr();
}

void SyntaxAnalyzer::StatIf()
{
	/*Prepare TerminalSymbol will be good */
	printf("StateIf-->");
	ProcessTermSym(lex_if, "Expected if\n");
	ProcessTermSym(lex_open_bracket, "Statement If: Expected (\n");
	BoolExpr();
	ProcessTermSym(lex_close_bracket, "Statement If: Expected )\n");
	Statement();
}

void SyntaxAnalyzer::ArgPrint()
{
	printf("ArgPrint-->");
	/* make a switch */
	if (c_l.type == lex_strlit)
		get_lex();
	else 
	if (BelongToFirstArExpr(c_l.type))
		ArExpr();
	else
		GoodBye("ArgPrint: Bad argument print\n");
}

void SyntaxAnalyzer::StatPrint()
{
	printf("StatPrint-->");
	ProcessTermSym(lex_print, "Statement Print: Expected print\n");
	ProcessTermSym(lex_open_bracket, "Statement Print:  Expected (\n");
	ArgPrint();
	while(c_l.type == lex_comma)
	{
		get_lex();
		ArgPrint();
	}
	ProcessTermSym(lex_close_bracket, "Statement Print:  Expected )\n");
}

void SyntaxAnalyzer::StatWhile()
{
	printf("StatWhile-->");
	ProcessTermSym(lex_while, "Statement While: Expected while\n");
	ProcessTermSym(lex_open_bracket, "Statement While: Expected (\n");
	BoolExpr();
	ProcessTermSym(lex_close_bracket, "Statement While: Expected )\n");
	Statement();
}

void SyntaxAnalyzer::ArgGmSt()
{
	/*make a switch */
	printf("ArgGmSt-->");
	if (!BelongToFirstArExpr(c_l.type))
		GoodBye("Statement ArgGmSt: Unexpected lexeme\n");
	ArExpr();
}

void SyntaxAnalyzer::StatGmSt()
{
	/* ProcName is bad name */
	printf("StatGmSt-->");
	switch(c_l.type)
	{
	case lex_end_turn:
		ProcName0();
		break;
	case lex_prod:
	case lex_build:
		ProcName1();
		break;
	case lex_buy:
	case lex_sell:
		ProcName2();
		break;
	case lex_curly_open_br:
		StatComp();
		break;
	default:
		GoodBye("Expected Game Statement\n");
	}
}

void SyntaxAnalyzer::ProcName0()
{
	printf("ProcName0-->");
	ProcessTermSym(lex_end_turn, "ProcName0: Expected end_turn\n");
	ProcessTermSym(lex_open_bracket, "ProcName0: Expected ( \n");
	ProcessTermSym(lex_close_bracket, "ProcName0: Expected ) \n");
}

void SyntaxAnalyzer::ProcName1()
{
	printf("ProcName1-->");
	if (c_l.type != lex_prod && c_l.type != lex_build)
		GoodBye("ProcName1: Expected prod or build\n");
	get_lex();
	ProcessTermSym(lex_open_bracket, "prod/build: Expected ( \n");
	ArgGmSt();		
	ProcessTermSym(lex_close_bracket, "prod/build: Expected ) \n");
}

void SyntaxAnalyzer::ProcName2()
{
	printf("ProcName2-->");
	if (c_l.type != lex_buy && c_l.type != lex_sell)
		GoodBye("ProcName2: Expected prod or build\n");
	get_lex();
	ProcessTermSym(lex_open_bracket, "buy/sell: Expected ( \n");
	ArgGmSt();
	ProcessTermSym(lex_comma, "buy/sell: Expected , \n");
	ArgGmSt();
	ProcessTermSym(lex_close_bracket, "buy/sell: Expected ) \n");
}
