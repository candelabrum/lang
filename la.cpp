#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "l.hpp"
#include "edges.hpp"
#include "lex.hpp"
#include "sa.hpp"

/* make in lex.cpp global variables belong to classes */
/* make more smaller big strings */
/* You can divide the state of the idenficator into 
		function processing and variable processing */

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
	list<lexeme>& get_lst() { return lst; }
};

bool FiniteStateMachine::IsErrorNow()
{
	return cur_st == 10; /* ten is state of error */
}

class LexicalAnalyzer
{
	FiniteStateMachine fsm;
public:
	list<lexeme>& start(FILE *f);	
};

FiniteStateMachine::FiniteStateMachine()
{
	cur_st = 0;
	current_line = 1;
	DelayNow = 0;
}

void FiniteStateMachine::make_step(char sym)
{
	feed(sym);
	if (DelayNow)
		feed(sym);
}

void FiniteStateMachine::feed(char sym)
{
	Edge *edge;
	int next_st;

	cur_lex.number_line = current_line;
	for(next_st = 0; next_st < size; next_st++)
	{
		edge = AdjMatrix[cur_st][next_st];
		if (edge && edge->condition(sym, cur_lex))
			break;
	}
	edge->transition(sym, cur_lex, lst);
	DelayNow = edge->IsDelay(sym);
	cur_st = next_st;
	if (sym == '\n')
		current_line++;
	if (sym == '@') /* It is a bad if, It must be in AdjMatr*/
	{
		cur_lex.prepare(sym, lex_fin);
		lst.add_node_to_end(cur_lex);
	}
}

list<lexeme>& LexicalAnalyzer::start(FILE *f)
{
	int c;
	
	for(;;)
	{
		c = fgetc(f);
		if (c == EOF)
		{
			fsm.make_step('@');
			break;
		}	
		fsm.make_step((char)c); /* maybe bad */
	}
	putchar('\n');
	printf("        String         ||       Type     ||   Line:\n");  
	printf("=====================================================\n");
	(fsm.get_lst()).print();
	
	return fsm.get_lst();
}

int main(int argc, char* const *argv)
{
	LexicalAnalyzer la;
	SyntaxAnalyzer sa;
	list<lexeme> lst;
	FILE *f;

	if (argc != 2)
	{
		printf("Wrong parameters\n");
		exit(1);
	}
	f = fopen(argv[1], "r");
	if (!f)
	{
		perror("fopen");
		exit(1);
	}
	lst = la.start(f);
	sa.Start(lst);
	lst.make_null();
	fclose(f);
	
	return 0;
}
