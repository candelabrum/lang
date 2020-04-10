#ifndef SYNTAXANALYZER_H_SENTRY
#define SYNTAXANALYZER_H_SENTRY

#include "l.hpp"
#include "rpn.hpp"
#include "rpn_list.hpp"

class SyntaxAnalyzer
{
/* 			--- Reverse Polish Notation(RPN) ---        */
	RPNList rpn_lst;
	void add_item(type_lexeme type);
/*  		--- Auxiliary part of this class ---		*/
	list<lexeme> lst;
	lexeme *c_l;
	bool IsFunctionZeroArg(type_lexeme t);
	bool IsFunctionOneArg(type_lexeme t);
	bool BelongToFirstArExpr(type_lexeme type);
	bool BelongToFirstBoolExpr(type_lexeme type);
	bool BelongToFirstStatement(type_lexeme type);
	bool IsCmpSign(type_lexeme type);
	void ProcessTermSym(type_lexeme t, const char *msg);
	void get_lex();
/* 			--- Alphabet of Non Terminal Symbols ---    */
	void Var(); 	  /* Variable 					(1)	*/
	void VarAux(); 	  /* Variable Auxiliary 		(2)	*/
	void ArExpr();	  /* Arithmetic expression 		(3)	*/ 
	void ArExpr1();	  /* Arithmetic expr.1			(4) */
	void ArExpr2();	  /* Arithmetic expr.2			(5)	*/
	void BoolExpr();  /* Boolean Expression 		(6) */
	void BoolExpr1(); /* Boolean Expression1		(7) */
	void BoolExpr2(); /* Boolean Expression2	 	(8) */
	void StatComp();  /* Statement Compound 		(10)*/
	void StatList();  /* List of Statements. First ---- */
	void Statement(); /* ------- 					(11)*/
	void GameStat();  /* Game statement 			(12)*/
	void Function();  /* ------- 					(13)*/
	void ArgPrint();  /* SubFunc of     Print   	----*/
	void StatIf(); 	  /* SubFunc of 	Statement   ----*/
	void StatAssign();/* SubFunc of 	Statement   ----*/
	void StatWhile(); /* SubFunc of 	Statement   ----*/
	void StatBegin(); /* SubFunc of 	Statement   ----*/
	void StatPrint(); /* SubFunc of 	Statement   ----*/
	void StatGmSt();  /* SubFunc of 	Statement   ----*/
	void ArgGmSt();   /* Argument of Game Statement ----*/
	void ProcName0(); /* SubFunc of 	GameStat    ----*//*bad*/
	void ProcName1(); /* SubFunc of 	GameStat    ----*//*names*/
	void ProcName2(); /* SubFunc of 	GameStat    ----*/
	void ArgsFunc0(); /* SubFunc of 	Function    ----*/
	void ArgsFunc1(); /* SubFunc of 	Function    ----*/
public:
	void Start(list<lexeme> a_lst);
};

class SAException
{
	lexeme lex;
	const char *comment;
public:
	SAException(lexeme& lex, const char *cmt);
	SAException(const SAException& other);
	const lexeme& GetLexeme() const { return lex; }
	const char* GetComment() const { return comment; }
};

#endif
