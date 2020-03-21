#ifndef EDGES_H_SENTRY
#define EDGES_H_SENTRY

#include <stdio.h>
#include "str.hpp"
#include "lex.hpp"
#include "l.hpp"

/* make a norm add_node_to_end with ptr end */
/* !!! In lexeme make field str instead lex */
/* Type lexeme set only end */

class Edge
{
public:
	virtual bool condition(char sym, lexeme& c_l) = 0;
	virtual void transition(char sym, lexeme& c_l, list<lexeme>& lst) = 0;
	virtual bool IsDelay(char sym) { return 0; }
	/* delay can be only state_to_home */
	/* delay work with condition. Delay always checks after condition check */
};

extern const int size;
extern Edge* AdjMatrix[11][11];

#endif
