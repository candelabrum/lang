#include <stdio.h>
#include "rpn.hpp"
#include "rpn_func.hpp"

class RPNFunMyId: public RPNFunc0
{
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
public:
	RPNFunMyId() {}
	virtual ~RPNFunMyId() {}
	virtual void print() const { printf("[my_id]"); }
	virtual	RPNFunction* Clone() const { return new RPNFunMyId(); }
};

class RPNFunTurn: public RPNFunc0
{
	RPNElem* EvaluateFun(RPNItem **stack) const
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
	RPNElem* EvaluateFun(RPNItem **stack) const
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
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
