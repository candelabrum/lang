#ifndef RPN_H_SENTRY
#define RPN_H_SENTRY

#include "lex.hpp"
#include "rpn_stack.hpp"

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
	static RPNElem* Pop(RPNElem **stack) {return 0;} 
};

struct RPNItem
{
	RPNElem *elem;
	RPNItem *next;
	RPNItem(RPNElem *a_elem) { elem = a_elem; next = 0;}
	void delete_elem()
	{
		if (elem)
        {
			elem = 0;
            delete elem; 
        }
	}
};

#endif
