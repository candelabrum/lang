#include <stdio.h>
#include <stdlib.h>
#include "lex.hpp"
#include "l.hpp"
#include "sa.hpp"
#include "rpn.hpp"

SAException::SAException(lexeme &a_lex, const char *cmt)
{
	lex = a_lex;
	comment = cmt;
}

void SyntaxAnalyzer::Start(list<lexeme> a_lst)
{
	lst = a_lst; 
	get_lex();
	printf("--------------------------------------------\n");
	StatList();
	ProcessTermSym(lex_fin, "Expected end of file. "
								"Probably you don't write ;\n");
	printf("\nAlready done\n");
}

void SyntaxAnalyzer::get_lex()
{
	c_l = &lst.get_data(0); /* a very bad copy */
	while(c_l && c_l->type == lex_com)
	{
		lst.next();
		c_l = &lst.get_data(0);
	}
	lst.next();
} 

void SyntaxAnalyzer::ProcessTermSym(type_lexeme t, const char *msg)
{
	if (c_l->type != t)
		throw SAException(*c_l, msg);
	get_lex();
}

/*void SyntaxAnalyzer::DeleteAllComments()
{
	lst.delete_nodes(lex_com);
}*/

void SyntaxAnalyzer::Var()
{
#ifdef DEBUG
	printf("Var-->");
#endif
	ProcessTermSym(lex_var, "Expected variable\n");
	VarAux();
}

void SyntaxAnalyzer::VarAux()
{
#ifdef DEBUG
	printf("VarAux-->");
#endif
	if (c_l->type == lex_open_sq_br)
	{
		get_lex();
		ArExpr();
		ProcessTermSym(lex_close_sq_br, "After variable: "
												"Expected ]\n");
	}
}

bool SyntaxAnalyzer::BelongToFirstArExpr(type_lexeme t)
{
	/* make a normal array of type_lexeme */
	return t == lex_var || t == lex_integ || t == lex_fractional ||
		t == lex_func_one || t == lex_func_zero || 
		t == lex_open_bracket || t == lex_plus || t == lex_minus;
}

void SyntaxAnalyzer::ArExpr()
{
#ifdef DEBUG
	printf("ArExpr-->");
#endif
	if (!BelongToFirstArExpr(c_l->type))
		throw SAException(*c_l, "Expected Arithmetic Expression"
											" with + and -\n");
	ArExpr1();
	while(c_l->type == lex_plus || c_l->type == lex_minus)
	{
		get_lex();
		ArExpr1();
		printf("+|-");/*C*/
		c_l->print();/*!*/
	}
}

void SyntaxAnalyzer::ArExpr1()
{
#ifdef DEBUG
	printf("ArExpr1-->");
#endif
	if (!BelongToFirstArExpr(c_l->type))
		throw SAException(*c_l, "Expected Arithmetic Expression"
											"with * and /\n");
	ArExpr2();
	while(c_l->type == lex_star || c_l->type == lex_slash)
	{
		get_lex();
		ArExpr2();
		printf("*|/");/*C*/
		c_l->print();/*!*/
	}
}

void SyntaxAnalyzer::ArExpr2()
{
#ifdef DEBUG
	printf("ArExpr2-->");
#endif
	if (c_l->type == lex_var)
		Var();
	else
	if (c_l->type == lex_func_one || c_l->type == lex_func_zero)
		Function();
	else
	if (c_l->type == lex_open_bracket)
	{
		get_lex();
		ArExpr();
		ProcessTermSym(lex_close_bracket, "Arithmetic Expression: "
													"Expected ) ");
	}	
	else 
	if (c_l->type == lex_integ || c_l->type == lex_fractional)
	{
		c_l->print();/*!*/
		get_lex();	
	}
	else
	if(c_l->type == lex_plus || c_l->type == lex_minus)
	{
		/* here processing lexeme unary minus */
		get_lex();
	}
	else
		throw SAException(*c_l, "Arithmetic Expression: "
											"Unexpected lexeme\n");
}

bool SyntaxAnalyzer::IsCmpSign(type_lexeme t)
{
	return t == lex_equality || t == lex_lss ||
		t == lex_gtr || t == lex_leq || t == lex_geq;
}

bool SyntaxAnalyzer::BelongToFirstBoolExpr(type_lexeme t)
{
	return t == lex_open_bracket || t == lex_neg ||
		BelongToFirstArExpr(t) || t == lex_open_sq_br ||
		t == lex_close_sq_br;
}


void SyntaxAnalyzer::BoolExpr()
{
#ifdef DEBUG
	printf("BoolExpr-->");
#endif
	if (!BelongToFirstBoolExpr(c_l->type))
		throw SAException(*c_l, "Expected Boolean Expression "
										"with <, >, etc\n");
	BoolExpr1();
	if (IsCmpSign(c_l->type))
	{
		get_lex();
		BoolExpr1();
	}
}

void SyntaxAnalyzer::BoolExpr1()
{
#ifdef DEBUG
	printf("BoolExpr1-->");
#endif
	if (!BelongToFirstBoolExpr(c_l->type))
		throw SAException(*c_l, "Expected Boolean Expression "
											"probably with |\n");
	BoolExpr2();
	while(c_l->type == lex_or)
	{
		get_lex();
		BoolExpr2();
	}
}

void SyntaxAnalyzer::BoolExpr2()
{
#ifdef DEBUG
	printf("BoolExpr2-->");
#endif
	if (!BelongToFirstBoolExpr(c_l->type))
		throw SAException(*c_l, "Expected Boolean Expression "
											"probably with |\n");
	BoolExpr3();
	while(c_l->type == lex_and)
	{
		get_lex();
		BoolExpr3();
	}
}

void SyntaxAnalyzer::BoolExpr3()
{
#ifdef DEBUG
	printf("BoolExpr3-->");
#endif
	if (c_l->type == lex_open_sq_br)
	{
		get_lex();
		BoolExpr();
		ProcessTermSym(lex_close_sq_br, "BoolExpression: "
											"Expected ] ");
	}
	else 
	if (BelongToFirstArExpr(c_l->type))
	{
		ArExpr();
		if (!IsCmpSign(c_l->type))
			throw SAException(*c_l, "BoolExpression: "
										"Expected <, >, =, <=, >=");
		get_lex();
		ArExpr();
	}
	else
	if (c_l->type == lex_neg)
	{
		get_lex();
		BoolExpr3();
	}
	else
		throw SAException(*c_l, "BoolExpression: "
									"Unexpected lexeme\n");
}

void SyntaxAnalyzer::ArgsFunc0()
{
#ifdef DEBUG
	printf("ArgsFunc0-->");
#endif
	ProcessTermSym(lex_open_bracket, "Function: Expected (\n");
	ProcessTermSym(lex_close_bracket, "Function: Expected )\n");
}

void SyntaxAnalyzer::ArgsFunc1()
{
//	get_lex();
#ifdef DEBUG
	printf("ArgsFunc1-->");
#endif
	ProcessTermSym(lex_open_bracket, "Function: Expected (\n");
	ArExpr();
	ProcessTermSym(lex_close_bracket, "Funcstion: Expected )\n");
}

void SyntaxAnalyzer::Function()
{
#ifdef DEBUG
	printf("Function-->");
#endif
	/* make a switch or maybe not*/
	if (c_l->type == lex_func_zero)
	{
		get_lex();
		ArgsFunc0();		
	}
	else 
	if (c_l->type == lex_func_one)
	{
		get_lex();
		ArgsFunc1();	
	}
	else
		throw SAException(*c_l, "It is not Name Function, but"
									"expected name Function \n");
}

void SyntaxAnalyzer::StatComp()
{
#ifdef DEBUG
	printf("StatComp-->");
#endif
	ProcessTermSym(lex_curly_open_br, "Statement Compound: "
												"Expected {\n");
    StatList();	
	ProcessTermSym(lex_curly_close_br, "Statement Compound: "
												"Expected }\n");
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
#ifdef DEBUG
	printf("StatList-->");
#endif
	if (!BelongToFirstStatement(c_l->type))
		throw SAException(*c_l, "Program must start with Statement" 
								" or Compound Statement "
								"must contains Statements: "
								"Expected Statement \n");
	Statement();
	while(c_l->type == lex_semicolon)
	{
		get_lex();
		Statement();
	}
	printf("StatList was end\n");
}

void SyntaxAnalyzer::Statement()
{
#ifdef DEBUG
	printf("Statement-->");
#endif
	switch(c_l->type)
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
		throw SAException(*c_l, "Expected Statement, but " 
										"this is not statement\n");
	}
}

void SyntaxAnalyzer::StatAssign()
{
	/* condition was check */
#ifdef DEBUG
	printf("StatAssign-->");
#endif
	if (c_l->type !=lex_var)
		throw SAException(*c_l, "StatAssignment : "
									"Expected Variable\n");
	Var();
	ProcessTermSym(lex_assignment, "Statement Assignment: "
												"Expected :=\n");
	ArExpr();
}

void SyntaxAnalyzer::StatIf()
{
	/*Prepare TerminalSymbol will be good */
#ifdef DEBUG
	printf("StateIf-->");
#endif
	ProcessTermSym(lex_if, "Expected if\n");
	ProcessTermSym(lex_open_bracket, "Statement If: Expected (\n");
	BoolExpr();
	ProcessTermSym(lex_close_bracket, "Statement If: Expected )\n");
	Statement();
}

void SyntaxAnalyzer::ArgPrint()
{
#ifdef DEBUG
	printf("ArgPrint-->");
#endif
	/* make a switch */
	if (c_l->type == lex_strlit)
		get_lex();
	else 
	if (BelongToFirstArExpr(c_l->type))
		ArExpr();
	else
		throw SAException(*c_l, "ArgPrint: Bad argument print\n");
}

void SyntaxAnalyzer::StatPrint()
{
#ifdef DEBUG
	printf("StatPrint-->");
#endif
	ProcessTermSym(lex_print, "Statement Print: Expected print\n");
	ProcessTermSym(lex_open_bracket, "Statement Print: "
												"Expected (\n");
	ArgPrint();
	while(c_l->type == lex_comma)
	{
		get_lex();
		ArgPrint();
	}
	ProcessTermSym(lex_close_bracket, "Statement Print: "
												"Expected )\n");
}

void SyntaxAnalyzer::StatWhile()
{
#ifdef DEBUG
	printf("StatWhile-->");
#endif
	ProcessTermSym(lex_while, "Statement While: Expected while\n");
	ProcessTermSym(lex_open_bracket, "Statement While: "
												"Expected (\n");
	BoolExpr();
	ProcessTermSym(lex_close_bracket, "Statement While: "
												"Expected )\n");
	Statement();
}

void SyntaxAnalyzer::ArgGmSt()
{
	/*make a switch */
	printf("ArgGmSt-->");
	if (!BelongToFirstArExpr(c_l->type))
		throw SAException(*c_l, "Statement ArgGmSt: "
										"Unexpected lexeme\n");
	ArExpr();
}

void SyntaxAnalyzer::StatGmSt()
{
	/* ProcName is bad name */
#ifdef DEBUG
	printf("StatGmSt-->");
#endif
	switch(c_l->type)
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
		throw SAException(*c_l, "Expected Game Statement\n");
	}
}

void SyntaxAnalyzer::ProcName0()
{
#ifdef DEBUG
	printf("ProcName0-->");
#endif
	ProcessTermSym(lex_end_turn, "ProcName0: Expected end_turn\n");
	ProcessTermSym(lex_open_bracket, "ProcName0: Expected ( \n");
	ProcessTermSym(lex_close_bracket, "ProcName0: Expected ) \n");
}

void SyntaxAnalyzer::ProcName1()
{
#ifdef DEBUG
	printf("ProcName1-->");
#endif
	if (c_l->type != lex_prod && c_l->type != lex_build)
		throw SAException(*c_l, "ProcName1: "
									"Expected prod or build\n");
	get_lex();
	ProcessTermSym(lex_open_bracket, "prod/build: Expected ( \n");
	ArgGmSt();		
	ProcessTermSym(lex_close_bracket, "prod/build: Expected ) \n");
}

void SyntaxAnalyzer::ProcName2()
{
#ifdef DEBUG
	printf("ProcName2-->");
#endif
	if (c_l->type != lex_buy && c_l->type != lex_sell)
		throw SAException(*c_l, "ProcName2: "
									"Expected prod or build\n");
	get_lex();
	ProcessTermSym(lex_open_bracket, "buy/sell: Expected ( \n");
	ArgGmSt();
	ProcessTermSym(lex_comma, "buy/sell: Expected , \n");
	ArgGmSt();
	ProcessTermSym(lex_close_bracket, "buy/sell: Expected ) \n");
}
