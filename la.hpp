#include "l.hpp"

class LAException
{
	const char *comment;
public:
	LAException(const char *a_comment) { comment = a_comment;}
	const char* GetComment() { return comment; }
};

class LexicalAnalyzer
{
	class FiniteStateMachine
	{
		list<lexeme> lst;	
		lexeme cur_lex;
		int current_line;
		int cur_st;
		bool DelayNow; /* maybe bad solution */
		void feed(char symbol);		
	public:
		FiniteStateMachine();
		bool IsErrorNow();
		void make_step(char symbol);
		list<lexeme> get_lst() { return lst; }
	};

	FiniteStateMachine fsm;
public:
	list<lexeme> start(FILE *f);	
	bool IsErrorNow() { return fsm.IsErrorNow(); }
};
