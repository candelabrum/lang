#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "l.hpp"
#include "edges.hpp"
#include "lex.hpp"

class FiniteStateMachine
{
	list<lexeme> lst;	
	lexeme cur_lex;
	int current_line;
	int cur_st;
	bool DelayNow; /* maybe bad solution */
public:
	FiniteStateMachine();
	void feed(char symbol);		
	void make_step(char symbol);
	list<lexeme>& get_lst() { return lst; }
};

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
}

list<lexeme>& LexicalAnalyzer::start(FILE *f)
{
	int c;
	
	for(;;)
	{
		c = fgetc(f);
		if (c == EOF)
		{
			fsm.feed('@');
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
	la.start(f);
	fclose(f);
	
	return 0;
}

