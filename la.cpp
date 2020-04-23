#include <stdio.h>
#include "l.hpp"
#include "edges.hpp"
#include "la.hpp"

bool LexicalAnalyzer::FiniteStateMachine::IsErrorNow()
{
	return cur_st == 10; /* ten is state of error */
}

LexicalAnalyzer::FiniteStateMachine::FiniteStateMachine()
{
	cur_st = 0;
	current_line = 1;
	DelayNow = 0;
}

void LexicalAnalyzer::FiniteStateMachine::make_step(char sym)
{
	feed(sym);
	if (DelayNow)
		feed(sym);
}

void LexicalAnalyzer::FiniteStateMachine::feed(char sym)
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

list<lexeme> LexicalAnalyzer::start(FILE *f)
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
	
	return fsm.get_lst();
}
