#include "rpn.hpp"
#include "rpn_func.hpp"

define MAX_LEN_CMD 30

class RPNFunMyId: public RPNFunc0
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
        RPNDouble dbl = new RPNDouble(eval_info.game->my_id());

		return &dbl;
	}
public:
	RPNFunMyId() {}
	virtual ~RPNFunMyId() {}
	virtual void print() const { printf("[my_id]"); }
	virtual	RPNFunction* Clone() const { return new RPNFunMyId(); }
};

class RPNFunTurn: public RPNFunc0
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		/* Here should be body */
		return 0;
	}
public:
	RPNFunTurn() {}
	virtual ~RPNFunTurn() {}
	virtual void print() const { printf("[turn]"); }
	virtual	RPNFunction* Clone() const { return new RPNFunTurn(); }
};

class RPNFunPlayers: public RPNFunc0
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		/* Here should be body */
		return 0;
	}
public:
	RPNFunPlayers() {}
	virtual ~RPNFunPlayers() {}
	virtual void print() const { printf("[players]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunPlayers(); 
	}
};

class RPNFunActivePlayers: public RPNFunc0
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
        RPNDouble *dbl;
        
        dbl = new RPNDouble(eval_info.game->gi->active_players());

		return dbl;
	}
public:
	RPNFunActivePlayers() {}
	virtual ~RPNFunActivePlayers() {}
	virtual void print() const { printf("[active_players]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunActivePlayers(); 
	}
};

class RPNFunSupply: public RPNFunc0
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
        RPNDouble *dbl;
        
        dbl = new RPNDouble(eval_info.game->gi->supply());

		return dbl;
	}
public:
	RPNFunSupply() {}
	virtual ~RPNFunSupply() {}
	virtual void print() const { printf("[supply]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunSupply(); 
	}
};

class RPNFunRawPrice: public RPNFunc0
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
        RPNDouble *dbl;
        
        dbl = new RPNDouble(eval_info.game->gi->raw_price());

		return dbl;
	}
public:
	RPNFunRawPrice() {}
	virtual ~RPNFunRawPrice() {}
	virtual void print() const { printf("[raw_price]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunRawPrice(); 
	}
};

class RPNFunDemand: public RPNFunc0
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		RPNDouble *dbl;
        
        dbl = new RPNDouble(eval_info.game->gi->demand());

		return dbl;
	}
public:
	RPNFunDemand() {}
	virtual ~RPNFunDemand() {}
	virtual void print() const { printf("[demand]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunDemand(); 
	}
};

class RPNFunProductionPrice: public RPNFunc0
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		RPNDouble *dbl;
        
        dbl = new RPNDouble(eval_info.game->gi->production_price());

		return dbl;
	}
public:
	RPNFunProductionPrice() {}
	virtual ~RPNFunProductionPrice() {}
	virtual void print() const { printf("[production_price]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunProductionPrice(); 
	}
};

class RPNFunMoney: public RPNFunc1
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		RPNDouble *res;
        double arg;
        
        arg = PopArgDouble();
        res = new RPNDouble(eval_info.game->gi->money(arg));

		return res;
	}
public:
	RPNFunMoney() {}
	virtual ~RPNFunMoney() {}
	virtual void print() const { printf("[money]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunMoney(); 
	}
};

class RPNFunRaw: public RPNFunc1
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		RPNDouble *res;
        double arg;
        
        arg = PopArgDouble();
        res = new RPNDouble(eval_info.game->gi->raw(arg));

		return res;
	}
public:
	RPNFunRaw() {}
	virtual ~RPNFunRaw() {}
	virtual void print() const { printf("[raw]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunRaw(); 
	}
};

class RPNFunProduction: public RPNFunc1
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		RPNDouble *res;
        double arg;
        
        arg = PopArgDouble();
        res = new RPNDouble(eval_info.game->gi->production(arg));

		return res;
	}
public:
	RPNFunProduction() {}
	virtual ~RPNFunProduction() {}
	virtual void print() const { printf("[production]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunProduction(); 
	}
};

class RPNFunFactories: public RPNFunc1
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		RPNDouble *res;
        double arg;
        
        arg = PopArgDouble();
        res = new RPNDouble(eval_info.game->gi->factories(arg));

		return res;
	}
public:
	RPNFunFactories() {}
	virtual ~RPNFunFactories() {}
	virtual void print() const { printf("[factories]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunFactories(); 
	}
};

class RPNFunManufactured: public RPNFunc1
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		RPNDouble *res;
        double arg;
        
        arg = PopArgDouble();
        res = new RPNDouble(eval_info.game->gi->manufactured(arg));

		return res;
	}
public:
	RPNFunManufactured() {}
	virtual ~RPNFunManufactured() {}
	virtual void print() const { printf("[manufactured]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunManufactured(); 
	}
};

class RPNFunResultRawSold: public RPNFunc1
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		RPNDouble *res;
        double a;
        
        a = PopArgDouble();
        res = new RPNDouble(eval_info.game->gi->result_raw_sold(a));

		return res;
	}
public:
	RPNFunResultRawSold() {}
	virtual ~RPNFunResultRawSold() {}
	virtual void print() const { printf("[result_raw_sold]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunResultRawSold(); 
	}
};

class RPNFunResultRawPrice: public RPNFunc1
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		RPNDouble *res;
        double a;
        
        a = PopArgDouble();
        res = new RPNDouble(eval_info.game->gi->result_raw_price(a));

		return res;
	}
public:
	RPNFunResultRawPrice() {}
	virtual ~RPNFunResultRawPrice() {}
	virtual void print() const { printf("[result_raw_price]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunResultRawPrice(); 
	}
};

class RPNFunResultProdBought: public RPNFunc1
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		RPNDouble *res
        double a;
        
        a = PopArgDouble();
        res = new RPNDouble(
            eval_info.game->gi->result_prod_bought(a));

		return res;
	}
public:
	RPNFunResultProdBought() {}
	virtual ~RPNFunResultProdBought() {}
	virtual void print() const { printf("[result_prod_bought]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunResultProdBought(); 
	}
};

class RPNFunResultProdPrice: public RPNFunc1
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
		RPNDouble *res;
        double a;
        
        a = PopArgDouble();
        res = new RPNDouble(
            eval_info.game->gi->result_prod_price(a));

		return res;
	}
public:
	RPNFunResultProdPrice() {}
	virtual ~RPNFunResultProdPrice() {}
	virtual void print() const { printf("[result_prod_price]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunResultProdPrice(); 
	}
};
/*					--- Game Procedures --- 					*/
class RPNFunBuy: public RPNFunc2
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
        char *str = new char[MAX_LEN_CMD];

        arg2 = PopArgDouble(eval_info.stack);
        arg1 = PopArgDouble(eval_info.stack);
        snprintf(str, MAX_LEN_CMD, "buy %d %d\n", arg1, arg2);
        
        eval_info.game->req.set_buy(str);

		return 0;
	}
public:
	RPNFunBuy() {}
	virtual ~RPNFunBuy() {}
	virtual void print() const { printf("[Buy]"); }
	virtual	RPNFunction* Clone() const { return new RPNFunBuy(); }
};

class RPNFunSell: public RPNFunc2
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
        char *str = new char[MAX_LEN_CMD];

        arg2 = PopArgDouble(eval_info.stack);
        arg1 = PopArgDouble(eval_info.stack);
        snprintf(str, MAX_LEN_CMD, "sell %d %d\n", arg1, arg2);
        
        eval_info.game->req.set_sell(str);

		return 0;
	}
public:
	RPNFunSell() {}
	virtual ~RPNFunSell() {}
	virtual void print() const { printf("[Sell]"); }
	virtual	RPNFunction* Clone() const { return new RPNFunSell(); }
};
 
class RPNFunProd: public RPNFunc1
{
	RPNElem* EvaluateFun(EvalInfo  &eval_info) const
	{
        char *str = new char[MAX_LEN_CMD];

        arg2 = PopArgDouble(eval_info.stack);
        snprintf(str, MAX_LEN_CMD, "prod %d\n", arg1);
        
        eval_info.game->req.set_prod(str);

		return 0;
	}
public:
	RPNFunProd() {}
	virtual ~RPNFunProd() {}
	virtual void print() const { printf("[Prod]"); }
	virtual	RPNFunction* Clone() const { return new RPNFunProd(); }
};

class RPNFunBuild: public RPNFunc1
{
	RPNElem* EvaluateFun(EvalInfo  &eval_info) const
	{
		char *str = new char[MAX_LEN_CMD];

        arg2 = PopArgDouble(eval_info.stack);
        snprintf(str, MAX_LEN_CMD, "build %d\n", arg1);
        
        eval_info.game->req.set_build(str);

		return 0;
	}
public:
	RPNFunBuild() {}
	virtual ~RPNFunBuild() {}
	virtual void print() const { printf("[Build]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunBuild();
	}
};

class RPNFunEndTurn: public RPNFunc0
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const
	{
        eval_info.game->me.make_move(eval_info.gi, eval_info.req);
        eva_info.req.disappear();   

        return 0;
	}
public:
	RPNFunEndTurn() {}
	virtual ~RPNFunEndTurn() {}
	virtual void print() const { printf("[EndTurn]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunEndTurn(); 
	}
};
