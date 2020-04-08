#include "rpn.hpp"
#include "rpn_list.hpp"
#include "rpn_func.hpp"
#include "rpn_types.hpp"
#include "lex.hpp"

/* Maybe better NOOP_CONST and NOOP_FUNC is better */
/* make encapsulation of couple rpn * */
struct couple_rpn_func
{
	RPNFunction *elem;
	type_lexeme type_lex;
};

struct couple_rpn_const
{
	RPNConst *elem;
	type_lexeme type_lex;
};

class RPNTableFunc
{
	couple_rpn_func *table;	
public:
	RPNTableFunc(couple_rpn_func *a_table = 0) { table = a_table; } 
	RPNFunction* search_by(type_lexeme type) const;
	/* There should have been a binary search here */
};

class RPNTableConst
{
	couple_rpn_const *table;	
public:
	RPNTableConst(couple_rpn_const *a_table = 0)
	{
		table = a_table; 
	}
	RPNConst* search_by(type_lexeme type) const;
	/* There should have been a binary search here */
};

RPNFunPlus Plus, *plus = &Plus;
RPNFunMinus Minus, *minus = &Minus;
RPNFunMultiply Mult, *mult = &Mult;
RPNFunDivision Div, *div = &Div;
RPNFunLess Less, *less = &Less;
RPNFunLeq Leq, *leq = &Leq;
RPNFunGreater Gtr, *gtr = &Gtr;
RPNFunGeq Geq, *geq = &Geq;
RPNFunAssign Assign, *assign = &Assign;
RPNFunInd Ind, *ind = &Ind;
RPNFunVar Var, *var = &Var;
RPNFunTakeAddr TakeAddr, *take_addr = &TakeAddr;

couple_rpn_func couple_func [] {
	{plus, lex_plus},
	{minus, lex_minus},
	{mult, lex_star},
	{div, lex_slash},
	{less, lex_lss},
	{leq, lex_leq},
	{gtr, lex_gtr},
	{geq, lex_geq},
	{assign, lex_assignment},
	{ind, lex_close_sq_br},
/*	{var, lex_var}, 		*/
	{take_addr, lex_take_addr},
	{0, lex_null}
};

RPNTableFunc TableFunc(couple_func);


RPNDouble Number(0), *number = &Number;

couple_rpn_const couple_const []{
	{number, lex_fractional},
	{number, lex_integ},
	{0, lex_null}
};

RPNTableConst TableConst(couple_const);

void RPNList::add_node(lexeme *c_l)
{
	RPNConst *elem_const, *new_elem_const;
	RPNFunction *elem_func, *new_elem_func;

	if (c_l->type == lex_var)
	{
		RPNFunVar *new_var = new RPNFunVar();

		new_var->set(c_l);
		add_node_to_end(new_var);
		return;
	}
	elem_func = TableFunc.search_by(c_l->type);	
	if (elem_func)
	{
		new_elem_func = elem_func->Clone();	
		add_node_to_end(new_elem_func);
		return;
	}
	elem_const = TableConst.search_by(c_l->type);
	new_elem_const = elem_const->Clone();
	new_elem_const->set(c_l->lex);
	add_node_to_end(new_elem_const);
}

void RPNList::add_node_to_end(RPNElem *elem)
{
	RPNItem *new_item = new RPNItem(elem); 

	if (end)
	{
		end->next = new_item;
		end = end->next;
		return;
	}
	head = new_item;
	end = new_item;
}

void RPNList::print() const
{
	RPNItem *tmp = head;
	
	while(tmp)
	{
		(tmp->elem)->print();
		printf("->");
		tmp = tmp->next;
	}
}

void RPNList::disappear()
{
	RPNItem *tmp;
	
	if (head)
		printf("DESTRUCTOR\n");
	while(head)
	{
		printf("\nKILL!\n");
		tmp = head;
		head = head->next;
		delete tmp;
	}
	head = 0;
	end = 0;
}

RPNFunction* RPNTableFunc::search_by(type_lexeme t) const
{
	int i = 0;

	while(table[i].type_lex != lex_null && table[i].type_lex != t)
		i++;
	
	return table[i].elem;
}

RPNConst* RPNTableConst::search_by(type_lexeme t) const
{
	int i = 0;

	while(table[i].type_lex != lex_null && table[i].type_lex != t)
		i++;
	
	return table[i].elem;
}
