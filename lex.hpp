#ifndef LEX_H_SENTRY
#define LEX_H_SENTRY

#include "str.hpp"

enum type_lexeme
{
	lex_integ,  			//("integer"),
	lex_fractional,			//("fractional"),
//	lex_ident,				//("identificator"),
	lex_com,				//("comment"),
	lex_strlit,				//("literal string"),
//	lex_serv_word,			//("key word"),
	lex_func,				//("name_function"),
	lex_var,				//("name_variable"),
	lex_undefined,			//("undefined"),
	lex_prog,				//("program"),
	lex_build, 				//("build"),
	lex_if,					//("if"),
	lex_while,				//("while"),
	lex_print,				//("print"),
	lex_buy,				//("buy"),
	lex_sell,				//("sell"),
	lex_prod,				//("prod"),
	lex_end_turn,			//("end_turn"),
	lex_plus,				//("+"),
	lex_minus,				//("-"),
	lex_slash,				//("/"),
	lex_star,				//("*"),
	lex_comma,				//(","),
	lex_semicolon,			//(";"),
	lex_equality,			//("="),
	lex_open_bracket,		//("("),
	lex_close_bracket,		//(")"),
	lex_curly_open_br,		//("{"),
	lex_curly_close_br,		//("}"),
	lex_open_sq_br,			//("["),
	lex_close_sq_br,		//("]"),
	lex_neg,				//("!"),
	lex_assignment,			//(":="),
	lex_lss,				//("<"),
	lex_leq,				//("<="),
	lex_gtr, 				//(">"),
	lex_geq,				//(">="),
	lex_neq,				//("!="),
	lex_and,				//("&"),
	lex_or, 				//("|"),
	lex_null				//NULL
};

struct couple
{
	const char* str;
	type_lexeme type_lex;
};

class Table
{
	const couple *table;	
public:
	Table(const couple *a_table) { table = a_table; } 
	const char* search_by(type_lexeme type) const;
	type_lexeme search_by(string& str) const;
};

struct lexeme
{
	int number_line;
	string lex;
	type_lexeme type;
	void add_symbol(char symbol);
	void set(int a_number_line, type_lexeme t);
	void reset();
	void prepare(char s, type_lexeme t);
	void print_type() const;
	void print() const;
	lexeme();
private:
	bool try_to_print(Table *t, type_lexeme type) const;
};

extern Table TableKeyWords;
extern Table TableDelimiters;
extern Table TablePrint;
extern const string str_delimiters;

#endif
