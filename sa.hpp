#ifndef SYNTAXANALYZER_H_SENTRY
#define SYNTAXANALYZER_H_SENTRY
#include "l.hpp"


class SyntaxAnalyzer
{
	list<lexeme> lst;
	lexeme c_l;
	void GoodBye(const char *str);
	bool BelongToFirstArExpr(type_lexeme type);
	void get_lex();
	void Var(); 	  /* Variable 					(1)	*/
	void VarAux(); 	  /* Variable Auxiliary 		(2)	*/
	void ArExpr();	  /* Arithmetic expression 		(3)	*/ 
	void ArExpr1();	  /* Arithmetic expr.1			(4) */
	void ArExpr2();	  /* Arithmetic expr.2			(5)	*/
	void BoolExpr();  /* Boolean Expression 		(6) */
	void BoolExpr1(); /* Boolean Expression1		(7) */
	void BoolExpr2(); /* Boolean Expression2	 	(8) */
	void BoolExpr3(); /* Boolean Expression3		(9) */
	void Begin();	  /* Begin list operators 		(10)*/
	void Statement(); /* ------- 					(11)*/
	void GameStat();  /* Game statement 			(12)*/
	void Function();  /* ------- 					(13)*/
	void ArgPrint();  /* SubFunc of     Print    ----*/
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
	void Start(list<lexeme>& a_lst);
};

class SException
{
	lexeme cur_lex;
	const char *comment;
public:
	SException(lexeme lex, const char *cmt);
	SException(const SException& other);
	lexeme& GetLexeme() { return cur_lex; }
	const char* GetComment() const { return comment; }
};

#endif
