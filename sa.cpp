#include <stdio.h>
#include <stdlib.h>
#include "lex.hpp"
#include "l.hpp"
#include "sa.hpp"

SException::SException(lexeme lex, const char *cmt)
{
	cur_lex = lex;
	comment = cmt;
}

void SyntaxAnalyzer::start(list<lexeme> a_lst)
{
	lst = a_lst; 
	get_lex();
	A();
	printf("\nAlready done\n");
}

void SyntaxAnalyzer::get_lex()
{
	lexeme *tmp;

	tmp = &lst.get_data(0);
	if (tmp)
		cur_lex = *tmp;
	c_type = cur_lex.type;
	lst.next();
}
	
void SyntaxAnalyzer::V()
{
	printf("V->name_var[A]");
	if (c_type == lex_var)
		get_lex();
	else
		throw SException(cur_lex, "It is not variable\n");
	if (c_type == lex_open_sq_br)
	{
		get_lex();
		A();
		if (c_type == lex_close_sq_br)
			get_lex();
		else
			throw SException(cur_lex, "It is not variable\n");
	}
}

void SyntaxAnalyzer::A()
{
	printf("A->A1");
	A1();
	while (c_type == lex_plus || c_type == lex_minus)
	{
		printf(" +- A1");
		get_lex();
		A1();
	}
}

void SyntaxAnalyzer::A1()
{
	printf("->A2");
	A2();
	while(c_type == lex_star || c_type == lex_slash)
	{
		printf("+-  A2");
		get_lex();
		A2();
	}
}

void SyntaxAnalyzer::A2()
{
	if (c_type == lex_var)
	{
		printf("->V");
		V();
	}
	else 
	if (c_type == lex_open_bracket)
	{
		get_lex();
		A();
		if (c_type == lex_close_bracket)
			get_lex();
		else 
			throw SException(cur_lex, "A2:Expected ) \n");
		printf("->(A)");
	}
	else 
	if (c_type == lex_fractional || c_type == lex_integ)
	{
		printf("->Number");
		get_lex();
	}
	else
		throw SException(cur_lex, "A2:Strange Lexeme \n");
}
