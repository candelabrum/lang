#ifndef RPN_LIST_H_SENTRY
#define RPN_LIST_H_SENTRY

#include "rpn.hpp"
#include "rpn_types.hpp"
#include "rpn_func.hpp"

struct RPNList
{
	RPNList(RPNItem *a_head = 0, RPNItem *a_end = 0) 
	{ 
		head = a_head; 
		end = a_end;
	} 
	RPNItem *head;
	RPNItem *end;
	void add_node(lexeme *lex);
	void add_node_to_end(RPNElem *elem);
	void disappear();
	void print() const;
};

class RPNNoop : public RPNElem
{
public:
	virtual ~RPNNoop(){};
	virtual void Evaluate(RPNItem **stack,
						RPNItem **cur_cmd) const {}
	void print() const { printf("Noop"); }
};


#endif
