#ifndef RPN_LIST_H_SENTRY
#define RPN_LIST_H_SENTRY

#include "rpn.hpp"
#include "rpn_types.hpp"
#include "rpn_func.hpp"
#include "rpn_go.hpp"
#include "rpn_far.hpp"
#include "rpn_fcmp.hpp"
#include "rpn_fbl.hpp"


struct RPNList : RPNItem
{
/* 					--- intermediate_classes --- 				*/
	RPNDouble Double;
	RPNConst *r_const = &Double;
	RPNFunPlus Plus;
	RPNFunction *r_func = &Plus;
/*	RPNOpGo Go;
	RPNOp *r_op = &Go;*/
	static const int len_int_cl = 2;
	RPNElem* intermediate_classes[len_int_cl] = {r_func, r_const};

/*							--- main ---						*/
	RPNList(RPNItem *a_head = 0, RPNItem *a_end = 0) 
	{ 
		head = a_head; 
		end = a_end;
		if (!(head || end))
		{
			RPNNoop *head_noop = new RPNNoop();
			RPNNoop *end_noop = new RPNNoop();

			head = new RPNItem(head_noop);
			end = new RPNItem(end_noop);
			head->next = end;
		}
	} 
	RPNItem *head;
	RPNItem *end;
	void add_node(lexeme *lex);
	void add_node_to_end(RPNElem *elem);
	void disappear() 
    { 
        if (head)
            head->Disappear(); 
	}
	void print() const { head->Print(); }
	void insert_jmp(RPNItem *old_label, RPNItem *new_label);
	RPNItem* get_head() { return head; }
	RPNItem* get_end() { return end; }
};

#endif
