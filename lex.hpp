#ifndef LEX_H_SENTRY
#define LEX_H_SENTRY

#include "str.hpp"

enum type_lexeme
{
/* 			---	Lexical and Syntax Analyzer ---				*/
	lex_integ,  			//("integer"),
	lex_fractional,			//("fractional"),
	lex_com,				//("comment"),
	lex_strlit,				//("literal string"),
	lex_func,				//("name_function"),
	lex_func_one,			//("function_one_arg"),
	lex_func_zero,			//("functioin_zero_arg"),
	lex_var,				//("name_variable"),
	lex_undefined,			//("undefined"),
	lex_fin,				//("@"),
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
	lex_null,				//NULL,
/*					--- Game Functions ---						*/
	lex_my_id, 				//("my_id"),
	lex_turn,				//("turn"),
	lex_players,			//("players"),
	lex_active_players,		//("active_players"),
	lex_supply,				//("supply"),
	lex_raw_price,			//("raw_price"),
	lex_demand,				//("demand"),
	lex_production_price,	//("production_price)",
	lex_money,				//("money"),
	lex_raw, 				//("raw"),
	lex_production,			//("production"),
	lex_factories,			//("factories"),
	lex_manufactured,		//("manufactured"),
	lex_result_raw_sold,	//(---)
	lex_result_raw_price,	//(---)
	lex_result_prod_bought, //(---)
	lex_result_prod_price,	//(---)
/*				--- Reverse Polish Notation --- 				*/
	lex_take_addr,			//("$"),
	lex_op_go_false,		//("!f"), 
	lex_op_go, 				//("!"),
	lex_noop				//("noop"),
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
	Table(const couple *a_table = 0) { table = a_table; } 
	const char* search_by(type_lexeme type) const;
	type_lexeme search_by(string& str) const;
	/* There should have been a binary search here */
};

struct lexeme
{
	int number_line;
	string lex;
	type_lexeme type;
	void add_symbol(char symbol);
	void set(int a_number_line, type_lexeme t);
	void reset();
	void prepare(char s, type_lexeme t); /* is bad function */
	void print_type() const;
	void print() const;
	bool is_func_one_arg();
	bool is_func_zero_arg();
	lexeme();
private:
	bool try_to_print(Table *t, type_lexeme type) const;
};


extern Table TableKeyWords;
extern Table TableDelimiters;
extern Table TablePrint;
extern const string str_delimiters;

#endif
