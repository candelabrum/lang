#ifndef RPN_H_SENTRY
#define RPN_H_SENTRY

#include "lex.hpp"

struct RPNItem;

class RPNElem
{
public:
	virtual ~RPNElem() {};
	virtual void Evaluate(RPNItem **stack,
								RPNItem **cur_cmd) const = 0;
	virtual void print() const = 0;
	virtual RPNElem* Convert2RPNElem(lexeme *l) const = 0;

protected:
	static void Push(RPNItem **stack, RPNElem *elem) {} 
	static RPNElem* Pop(RPNItem **stack) { return 0; } 
};

struct RPNItem
{
    RPNItem(RPNItem *a_next = 0) { next = a_next; }
	bool IsEmpty() const { return next; }
	void Push(RPNElem* elem); 
   	RPNElem* Pop();
	void Print() const;
	void Disappear(); 

	RPNElem *elem;
    RPNItem *next;

	RPNItem(RPNElem *a_elem) { elem = a_elem; next = 0;}
	void delete_elem();
};

struct EvalInfo
{
    RPNItem **cur_cmd;
    RPNItem stack;
};

#endif
