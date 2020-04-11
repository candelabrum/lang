#include "lex.hpp"
#include "rpn.hpp"
#include "rpn_func.hpp"
#include "rpn_types.hpp"

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
	RPNFunProductionPrice ProdPr, *production_price = &ProdPr;
	RPNFunMoney Money, *money = &Money;
	RPNFunRaw Raw, *raw = &Raw;
	RPNFunProduction Production, *production = &Production;
	RPNFunFactories Factories, *factories = &Factories;
	RPNFunManufactured Manufactured, *manufactured = &Manufactured;
	RPNFunResultRawSold ResRawSold, *result_raw_sold = &ResRawSold;
	RPNFunResultRawPrice ResRawPr, *result_raw_price = &ResRawPr;
	RPNFunResultProdBought ResPrBt, *result_prod_bought = &ResPrBt;
	RPNFunResultProdPrice ResPrPrc, *result_prod_price = &ResPrPrc;
/*					--- Game Procedures ---						*/
	RPNFunBuy Buy, *buy = &Buy;
	RPNFunSell Sell, *sell= &Sell;
	RPNFunBuild Build, *build = &Build;
	RPNFunProd Prod, *prod = &Prod;
	RPNFunEndTurn EndTurn, *end_turn = &EndTurn;
	RPNFunPrint Print, *print = &Print;

	couple_rpn_func table[42] {
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
		{result_raw_price, lex_result_raw_price},
		{result_prod_bought, lex_result_prod_bought},
		{result_prod_price, lex_result_prod_price},
/*					--- Game Procedures ---						*/
		{buy, lex_buy},
		{sell, lex_sell},
		{build, lex_build},
		{prod, lex_prod},
		{end_turn, lex_end_turn},
		{print, lex_print},
		{0, lex_null}
	};

public:
	RPNFunction* search_by(type_lexeme type) const;
	/* There should have been a binary search here */
};

RPNFunction* RPNTableFunc::search_by(type_lexeme t) const
{
	int i = 0;

	while(table[i].type_lex != lex_null && table[i].type_lex != t)
		i++;
	
	return table[i].elem;
}

RPNElem* RPNFunction::Convert2RPNElem(lexeme *c_l) const
{
	static RPNTableFunc TableFunc;
	RPNFunction *elem_func, *new_elem_func;
	
	if (c_l->type == lex_var)
	{
		RPNFunVar *new_var = new RPNFunVar();

		new_var->set(c_l);
		return new_var;
	}

	elem_func = TableFunc.search_by(c_l->type);	

	if (!elem_func)
		return 0;

	new_elem_func = elem_func->Clone();

	return new_elem_func;
}

RPNElem* RPNFuncArithm::EvaluateFun(RPNItem *stack) const
{
    RPNDouble *dbl;
    double arg1, arg2, res;

    arg1 = PopArg(stack);
    arg2 = PopArg(stack);
    
    res = EvalOperation(arg1, arg2);
    
    dbl = new RPNDouble(res);
    
    return dbl;
}

RPNElem* RPNFuncCmp::EvaluateFun(RPNItem *stack) const
{
    RPNBool *Boolean;
    double arg1, arg2;
    bool res;

    arg1 = PopArg(stack);
    arg2 = PopArg(stack);
    
    res = EvalOperation(arg1, arg2);
    
    Boolean = new RPNBool(res);
    
    return Boolean;
}

void RPNFunction::Evaluate(EvalInfo &eval_info) const
{
	RPNElem *res = EvaluateFun(eval_info.stack);
    RPNItem **cur_cmd = eval_info.cur_cmd;

	if (res)
		(eval_info.stack)->Push(res);

	*cur_cmd = (*cur_cmd)->next;
}

void RPNFunVar::print() const 
{ 
	printf("[");
	name.print();
	printf("]");
}

double RPNFunction::PopArg(RPNItem *stack)
{
    RPNDouble *dbl;

    dbl = dynamic_cast<RPNDouble*>(stack->Pop());
    if (!dbl)
    {
        fprintf(stderr, "GOOD BYE: IN FUNC2 has not int \n");
        exit(1);
    }
    
    return dbl->Get();
}

bool RPNFunction::PopArg(RPNItem *stack)
{
    RPNBool *bool;

    bool = dynamic_cast<RPNBool*>(stack->Pop());
    if (!bool)
    {
        fprintf(stderr, "GOOD BYE: IN FUNC2 has not int \n");
        exit(1);
    }
    
    return bool->Get();
}

RPNElem* RPNPrint::EvaluateFun(RPNItem *stack) const
{
    while(!stack.IsEmpty())
    {
        RPNElem *arg;
           
        arg = stack->Pop();
        arg->print();
    }

	return 0;
}
