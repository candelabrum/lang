#include "rpn.hpp"
#include "rpn_list.hpp"
#include "rpn_func.hpp"
#include "rpn_types.hpp"
#include "rpn_go.hpp"
#include "lex.hpp"

/* Maybe better NOOP_CONST and NOOP_FUNC is better */
/* make encapsulation of couple rpn * */

struct couple_rpn_op
{
	RPNOp *elem;
	type_lexeme type_lex;
};

class RPNTableFunc
{
	struct couple_rpn_func
	{
		RPNFunction *elem;
		type_lexeme type_lex;
	};
/*					--- General Functions ---					*/
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
/*					--- Functions for Game ---					*/
	RPNFunMyId MyId, *my_id = &MyId;
	RPNFunTurn Turn, *turn = &Turn;
	RPNFunPlayers Players, *players = &Players;
	RPNFunActivePlayers ActPlayers, *active_players = &ActPlayers;
	RPNFunSupply Supply, *supply = &Supply;
	RPNFunRawPrice RawPrice, *raw_price = &RawPrice;
	RPNFunDemand Demand, *demand = &Demand;
	RPNFunProductionPrince ProdPr, *production_price = &ProdPr;
	RPNFunMoney Money, *money = &Money;
	RPNFunRaw Raw, *raw = &Raw;
	RPNFunProduction Production, *production = &Production;
	RPNFunFactories Factories, *factories = &Factories;
	RPNFunManufactured Manufactured, *manufactured = &Manufactured;
	RPNFunResultRawSold ResRawSold, *result_raw_sold = &ResRawSold;
	RPNFunResultRawPrice ResRawPr, *result_raw_price = &ResRawPr;
	RPNFunResultProdBought ResPrBt, *result_prod_bought = &ResPrBt;
	RPNFunResultProdPrice ResPrPrc, *result_prod_price = &ResPrPrc;
/*						--- Game Procs ---						*/
	RPNFunBuy Buy, *buy = &Buy;
	RPNFunSell Sell, *sell= &Sell;
	RPNFunBuild Build, *build = &Build;
	RPNFunProd Prod, *prod = &Prod;
	RPNFunEndTurn EndTurn, *end_turn = &EndTurn;

	couple_rpn_func table[] {
/*					--- General functions ---					*/
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
/*		{var, lex_var}, 		*/
		{take_addr, lex_take_addr},
		{equal, lex_equality},
		{_or, lex_or},
		{_and, lex_and},
/*					--- Functions for Game ---					*/
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
/*					--- Game Procedures ---						*/
		{buy, lex_buy},
		{sell, lex_sell},
		{build, lex_build},
		{prod, lex_prod},
		{end_turn, lex_end_turn},
		{0, lex_null}
	};

public:
	RPNFunction* search_by(type_lexeme type) const;
	/* There should have been a binary search here */
};

class RPNTableConst
{
	struct couple_rpn_const
	{
		RPNConst *elem;
		type_lexeme type_lex;
	};

	RPNDouble Number(0), *number = &Number;
	
	couple_rpn_const table[]{
		{number, lex_fractional},
		{number, lex_integ},
		{0, lex_null}
	};

public:
	RPNConst* search_by(type_lexeme type) const;
	/* There should have been a binary search here */
};

class RPNTableOp
{
	RPNOpGo OpGo, *op_go = &OpGo;
	RPNOpGoFalse OpGoFalse, *op_go_false = &OpGoFalse;
	RPNNoop Noop, *noop = &Noop;

	couple_rpn_op table[] {
		{op_go, lex_op_go},
		{op_go_false, lex_op_go_false},
		{noop, lex_noop},
		{0, lex_null}
	};

public:
	RPNOp* search_by(type_lexeme type) const;
	/* There should have been a binary search here */
};

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
