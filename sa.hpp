#ifndef SYNTAXANALYZER_H_SENTRY
#define SYNTAXANALYZER_H_SENTRY

#include "l.hpp"
class SyntaxAnalyzer
{
	list<lexeme> lst;
	lexeme cur_lex;
	type_lexeme c_type;
	void get_lex();
	void V();
	void A();
	void A1();
	void A2();
	void F();
	void Arg();
	void I();
	void N();
	void SL();
public:
	void start(list<lexeme> lst);
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
