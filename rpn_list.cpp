#include "rpn.hpp"
#include "rpn_list.hpp"
#include "rpn_func.hpp"
#include "rpn_types.hpp"
#include "rpn_go.hpp"
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

struct couple_rpn_op
{
	RPNOp *elem;
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

class RPNTableOp
{
	couple_rpn_op *table;	
public:
	RPNTableOp(couple_rpn_op *a_table = 0)
	{
		table = a_table; 
	}
	RPNOp* search_by(type_lexeme type) const;
	/* There should have been a binary search here */
};


couple_rpn_func couple_game_func[] {
	{my_id, lex_my_id},
	{turn, lex_turn},
	{players, lex_players},
	{active_players, lex_active_players},
	{supply, lex_supply},
	{raw_price, lex_raw_price},
	{demand, lex_demand},
	{production_price, lex_production_price},
	{money, lex_money},
	{raw, lex_raw},
	{production, lex_production},
	{factories, lex_factories},
	{manufactured, lex_manufactured},
	{result_raw_sold, lex_result_raw_sold},
	{result_raw_price, lex_result_price},
	{result_prod_bought, lex_result_prod_bought},
	{result_prod_price, lex_result_prod_price},
	{0, lex_null}
};

RPNTableFunc TableGameFunc(couple_game_func);

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
RPNFunEqual Equal, *equal = &Equal;
RPNFunOr Or, *_or = &Or;
RPNFunAnd And, *_and = &And;
RPNFunNot Not, *_not = &Not;

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
	{equal, lex_equality},
	{_or, lex_or},
	{_and, lex_and},
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

RPNOpGo OpGo, *op_go = &OpGo;
RPNOpGoFalse OpGoFalse, *op_go_false = &OpGoFalse;
RPNNoop Noop, *noop = &Noop;

couple_rpn_op couple_op [] {
	{op_go, lex_op_go},
	{op_go_false, lex_op_go_false},
	{noop, lex_noop},
	{0, lex_null}
};

RPNTableOp TableOp(couple_op);

void RPNList::add_node(lexeme *c_l)
{
	RPNElem *new_elem;
	
	for(int i = 0; intermediate_classes[i]; i++)
	{
		new_elem = intemediate_classes[i]::Convert2RPNElem(c_l);		   if (!new_elem)
			break;
	}
	add_node(new_elem);
}

void RPNList::insert_jmp(RPNItem *jump_label,
									RPNItem *place_label)
{
	RPNLabel *new_label= new RPNLabel(place_label);

	delete jump_label->elem;

	jump_label->elem = new_label;
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

RPNOp* RPNTableOp::search_by(type_lexeme t) const
{
	int i = 0;

	while(table[i].type_lex != lex_null && table[i].type_lex != t)
		i++;
	
	return table[i].elem;
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
