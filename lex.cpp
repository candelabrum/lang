#include "str.hpp"
#include "lex.hpp"
#include "l.hpp"

const string str_delimiters("+-/*;=(){},[]!");

const couple delimiters [] = {
	{"+", lex_plus},
	{"-", lex_minus},
	{"/", lex_slash},
	{"*", lex_star},
	{",", lex_comma},
	{";", lex_semicolon},
	{"=", lex_equality},
	{"(", lex_open_bracket},
	{")", lex_close_bracket},
	{"{", lex_curly_open_br},
	{"}", lex_curly_close_br},
	{"[", lex_open_sq_br},
	{"]", lex_close_sq_br},
	{"!",  lex_neg},
	{":=", lex_assignment},
	{"<=", lex_leq},
	{">=", lex_geq},
	{">", lex_gtr},
	{"<", lex_lss},
	{"!=", lex_neq},
	{"&", lex_and},
	{"|", lex_or},
	{0, lex_null} 
};

const couple key_words[] = {
	{"program", lex_prog},
	{"if", lex_if},
	{"while", lex_while},
	{"print", lex_print},
	{"buy",	lex_buy},
	{"sell", lex_sell},
	{"prod", lex_prod},
	{"build", lex_build},
	{"end_turn", lex_end_turn},
	{0, lex_null}
};

const couple for_print[] = {
	{"variable", lex_var},
	{"func_one_arg", lex_func_one},
	{"func_zero_arg", lex_func_zero},
	{"integer", lex_integ},
	{"fractional", lex_fractional},
	{"comment", lex_com},
	{"string literal", lex_strlit},
	{"undefined", lex_undefined},
	{"lex final", lex_fin},
	{0, lex_null}
};

const char* FunctionOneArg[] = {
	"?money",
	"?raw",
	"?production",
	"?factories",
	"?manufactured",
	"?result_raw_sold",
	"?result_raw_price",
	"?result_prod_bought",
	"?result__prod_price",
	0
};

const char* FunctionZeroArg[] = {  /* Can I move { to next line? */
	"?my_id",
	"?turn",
	"?players",
	"?active_players",
	"?supply",
	"?raw_price",
	"?demand",
	"?production_price",
	0
};

Table TableDelimiters(delimiters);
Table TableKeyWords(key_words);
Table TablePrint(for_print);

Table *AllTables[] = {&TableDelimiters, &TableKeyWords, &TablePrint, 0};

const char* Table::search_by(type_lexeme t) const
{
	int i = 0;

	while(table[i].type_lex != lex_null && table[i].type_lex != t)
		i++;
	
	return table[i].str;
}

type_lexeme Table::search_by(string& key) const
{
	int i = 0;

	while(table[i].str && !key.is_equal(table[i].str))
		i++;
	
	return table[i].type_lex; 
}

/*  There should have been a binary search here */
bool lexeme::is_func_one_arg()
{
	return lex.any_str_equal(FunctionOneArg);
}

bool lexeme::is_func_zero_arg()
{
	return lex.any_str_equal(FunctionZeroArg);
}

void lexeme::prepare(char s, type_lexeme t) /* is bad function */
{
	reset();
	type = t;
	add_symbol(s);
}

void lexeme::add_symbol(char symbol)
{
	lex.add_to_len(1);    /* need in resize */	
	lex[lex.get_len() - 1] = symbol; 
}

bool lexeme::try_to_print(Table *t, type_lexeme type) const
{
	const char *str;

	str = t->search_by(type);
	if (str)
		printf("%14.14s", str);
	
	return str;
}

void lexeme::print_type() const
{
	bool success;

	for(int i = 0; AllTables[i]; i++)
	{
		success = try_to_print(AllTables[i], type);
		if (success)
			return;
	}
}

void lexeme::set(int a_number_line, type_lexeme t)
{
	number_line = a_number_line;
	type = t;
}

void lexeme::reset() 
{ 
	if (lex.get_len() > 0)
		lex.add_to_len(-lex.get_len());
	type = lex_undefined;
/*	number_line = 1; !!! */
}

lexeme::lexeme()
{
	number_line = 1;
	type = lex_undefined;
}

void lexeme::print() const
{
	lex.print_f();
	printf(" || ");
	print_type();
	printf(" || ");
	printf(" %5.3d\n", number_line); 
}


