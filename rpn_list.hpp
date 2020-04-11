#ifndef RPN_LIST_H_SENTRY
#define RPN_LIST_H_SENTRY

#include "rpn.hpp"
#include "rpn_types.hpp"
#include "rpn_func.hpp"
#include "rpn_go.hpp"

struct RPNList
{
/* 					--- intermediate_classes --- 				*/
	RPNDouble Double;
	RPNConst *r_const = &Double;
	RPNFunPlus Plus;
	RPNFunction *r_func = &Plus;
	RPNOpGo Go;
	RPNOp *r_op = &Go;
	RPNElem* intermediate_classes[4] = {r_const, r_func, r_op, 0};

/*							--- main ---						*/
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
	void insert_jmp(RPNItem *old_label, RPNItem *new_label);
	RPNItem* get_head() { return head; }
	RPNItem* get_end() { return end; }
};

#endif
