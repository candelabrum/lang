#include <stdio.h>
#include <stdlib.h>
#include "lex.hpp"
#include "l.hpp"
#include "sa.hpp"
#include "rpn.hpp"
#include "rpn_list.hpp"

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
	printf("PRINT LIST\n");
	rpn_lst.print();
	rpn_lst.disappear();
	printf("\nAlready done\n");
}

void SyntaxAnalyzer::get_lex()
{
	c_l = &lst.get_data(0); 
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

void SyntaxAnalyzer::Var()
{
#ifdef DEBUG
	printf("Var-->");
#endif
	if (c_l->type == lex_var)
		rpn_lst.add_node(c_l);
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
		rpn_lst.add_node(c_l); /* was lex_ind */
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
	lexeme *operation;
#ifdef DEBUG
	printf("ArExpr-->");
#endif
	if (!BelongToFirstArExpr(c_l->type))
		throw SAException(*c_l, "Expected Arithmetic Expression"
											" with + and -\n");
	ArExpr1();
	while(c_l->type == lex_plus || c_l->type == lex_minus)
	{
		operation = c_l; /* RPN */
		get_lex();
		ArExpr1();
		printf("+|-");/*C*/
		rpn_lst.add_node(operation);	
	}
}

void SyntaxAnalyzer::ArExpr1()
{
	lexeme *operation;
#ifdef DEBUG
	printf("ArExpr1-->");
#endif
	if (!BelongToFirstArExpr(c_l->type))
		throw SAException(*c_l, "Expected Arithmetic Expression"
											"with * and /\n");
	ArExpr2();
	while(c_l->type == lex_star || c_l->type == lex_slash)
	{
		operation = c_l;
		get_lex();
		ArExpr2();
		printf("*|/");/*C*/
		rpn_lst.add_node(operation);/*!*/
	}
}

void SyntaxAnalyzer::ArExpr2()
{
#ifdef DEBUG
	printf("ArExpr2-->");
#endif
	if (c_l->type == lex_var)
	{
		Var();
		add_operation(lex_take_addr);
	}
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
	//	c_l->print();/*!*/
		rpn_lst.add_node(c_l);
		get_lex();	
	}
	else
	if(c_l->type == lex_plus || c_l->type == lex_minus)
	{
		/* here processing lexeme unary minus and plus */
		/* BAD !!! IT CAN NOT WORK !!! *? */
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
		BelongToFirstArExpr(t) || t == lex_open_sq_br;
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
	lexeme *operation;
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
		operation = c_l;
		get_lex();
		ArExpr();
		rpn_lst.add_node(operation);
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
	// make a switch or maybe not 
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
	default:
	//Maybe make first for begin and prepare probably error
		throw SAException(*c_l, "Expected Statement, but " 
										"this is not statement\n");
	}
}

void SyntaxAnalyzer::StatAssign()
{
	lexeme *assign;
	/* condition was check */
#ifdef DEBUG
	printf("StatAssign-->");
#endif
	if (c_l->type !=lex_var)
		throw SAException(*c_l, "StatAssignment : "
									"Expected Variable\n");

	Var();
	assign = c_l;
	ProcessTermSym(lex_assignment, "Statement Assignment: "
												"Expected :=\n");
	ArExpr();
	rpn_lst.add_node(assign);
}

void SyntaxAnalyzer::add_operation(type_lexeme t)
{
	lexeme *new_lex = new lexeme();

	new_lex->type = t;
	new_lex->number_line = c_l->number_line;
	rpn_lst.add_node(new_lex);

	delete new_lex;
}

void SyntaxAnalyzer::StatIf()
{
	RPNItem *place_noop, *place_label;
#ifdef DEBUG
	printf("StateIf-->");
#endif
	ProcessTermSym(lex_if, "Expected if\n");
	ProcessTermSym(lex_open_bracket, "Statement If: Expected (\n");
	BoolExpr();
/* !!! */	
	add_operation(lex_noop);
	place_noop = rpn_lst.get_end();
	ProcessTermSym(lex_close_bracket, "Statement If: Expected )\n");
	add_operation(lex_op_go_false);
	Statement();
	place_label = rpn_lst.get_end();
	rpn_lst.insert_jmp(place_noop, place_label);/*was label noop*/
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
	RPNItem *Again, *JmpAgain, *Escape, *JmpEscape;
#ifdef DEBUG
	printf("StatWhile-->");
#endif
	ProcessTermSym(lex_while, "Statement While: Expected while\n");
	ProcessTermSym(lex_open_bracket, "Statement While: "
												"Expected (\n");
	Again = rpn_lst.get_end();
	BoolExpr();

	add_operation(lex_noop);
	JmpEscape = rpn_lst.get_end();
	add_operation(lex_op_go_false);

	ProcessTermSym(lex_close_bracket, "Statement While: "
												"Expected )\n");
	Statement();
	add_operation(lex_noop);
	JmpAgain = rpn_lst.get_end();
	
	rpn_lst.insert_jmp(JmpAgain, Again);
	Escape = rpn_lst.get_end();
	rpn_lst.insert_jmp(JmpEscape, Escape);

	add_operation(lex_op_go);
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
