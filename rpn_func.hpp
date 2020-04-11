#ifndef RPN_FUNC_H_SENTRY
#define RPN_FUNC_H_SENTRY

#include "rpn_stack.hpp"
#include "rpn.hpp"
#include "lex.hpp"
#include <stdio.h>

class RPNFunction : public RPNElem
{
	virtual RPNElem* EvaluateFun(RPNItem **stack) const = 0;
	void Evaluate(RPNItem** stack, 
								RPNItem  **cur_cmd) const;
public:
	virtual ~RPNFunction() {};
	virtual	RPNFunction* Clone() const = 0;
	RPNElem* Convert2RPNElem(lexeme *c_l) const;
};

class RPNFunc2 : public RPNFunction 
{
public:
	virtual	RPNFunction* Clone() const = 0;
};

class RPNFunc1 : public RPNFunction 
{
public:
	virtual	RPNFunction* Clone() const = 0;
};

class RPNFunc0 : public RPNFunction 
{
public:
	virtual	RPNFunction* Clone() const = 0;
};

class RPNFunPlus : public RPNFunc2
{
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
public:
	RPNFunPlus() {}
	virtual ~RPNFunPlus() {}
	virtual void print() const { printf("[+]"); }
	virtual	RPNFunction* Clone() const { return new RPNFunPlus(); }
};

class RPNFunMinus : public RPNFunc2
{
public:
	RPNFunMinus() {}
	virtual ~RPNFunMinus() {}
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
	virtual	RPNFunction* Clone() const { return new RPNFunMinus(); }

	virtual void print() const { printf("[-]"); }
};

class RPNFunMultiply : public RPNFunc2
{
public:
	RPNFunMultiply() {}
	virtual ~RPNFunMultiply() {}
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
	virtual void  print() const { printf("[*]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunMultiply(); 
	}
};

class RPNFunDivision : public RPNFunc2
{
public:
	RPNFunDivision() {}
	virtual ~RPNFunDivision() {}
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
	virtual void print() const { printf("[/]"); }
	virtual	RPNFunction* Clone() const
	{ 
		return new RPNFunDivision(); 
	}
};

class RPNFunLess: public RPNFunc2
{
public:
	RPNFunLess() {}
	virtual ~RPNFunLess() {}
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
	virtual void print() const { printf("[<]"); }
	virtual	RPNFunction* Clone() const
	{ 
		return new RPNFunLess(); 
	}
};

class RPNFunGreater: public RPNFunc2
{
public:
	RPNFunGreater() {}
	virtual ~RPNFunGreater() {}
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
	virtual void print() const { printf("[>]"); }
	virtual	RPNFunction* Clone() const
	{ 
		return new RPNFunGreater(); 
	}
};

class RPNFunLeq: public RPNFunc2
{
public:
	RPNFunLeq() {}
	virtual ~RPNFunLeq() {}
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
	virtual void print() const { printf("[<=]"); }
	virtual	RPNFunction* Clone() const
	{ 
		return new RPNFunLeq(); 
	}

};

class RPNFunGeq: public RPNFunc2
{
public:
	RPNFunGeq() {}
	virtual ~RPNFunGeq() {}
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
	virtual void print() const { printf("[>=]"); }
	virtual	RPNFunction* Clone() const
	{ 
		return new RPNFunGeq(); 
	}
};

class RPNFunEqual: public RPNFunc2
{
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
public:
	RPNFunEqual() {}
	virtual ~RPNFunEqual() {}
	virtual void print() const { printf("[=]"); }
	virtual	RPNFunction* Clone() const { return new RPNFunEqual();}
};

class RPNFunOr: public RPNFunc2
{
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
public:
	RPNFunOr() {}
	virtual ~RPNFunOr() {}
	virtual void print() const { printf("[|]"); }
	virtual	RPNFunction* Clone() const { return new RPNFunOr();}
};

class RPNFunAnd: public RPNFunc2
{
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
public:
	RPNFunAnd() {}
	virtual ~RPNFunAnd() {}
	virtual void print() const { printf("[&]"); }
	virtual	RPNFunction* Clone() const { return new RPNFunAnd();}
};

class RPNFunNot: public RPNFunc2
{
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
public:
	RPNFunNot() {}
	virtual ~RPNFunNot() {}
	virtual void print() const { printf("[!]"); }
	virtual	RPNFunction* Clone() const { return new RPNFunNot();}
};

class RPNFunInd : public RPNFunc2
{
public:
	RPNFunInd() {}
	virtual ~RPNFunInd() {}
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
	virtual void print() const { printf("[[]]");}
	virtual	RPNFunction* Clone() const
	{ 
		return new RPNFunInd(); 
	}
};

class RPNFunAssign : public RPNFunc2
{
public:
	RPNFunAssign() {}
	virtual ~RPNFunAssign() {}
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
	virtual void print() const { printf("[:=]");}
	virtual	RPNFunction* Clone() const
	{ 
		return new RPNFunAssign(); 
	}
};

class RPNFunTakeAddr: public RPNFunc1
{
public:
	RPNFunTakeAddr() {}
	virtual ~RPNFunTakeAddr() {}
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
	virtual void print() const { printf("[$]");}
	virtual	RPNFunction* Clone() const
	{ 
		return new RPNFunTakeAddr(); 
	}
};

class RPNFunVar: public RPNFunc0
{
	string name;
public:
	RPNFunVar() {}
	virtual ~RPNFunVar() {}
	void set(lexeme *c_l) { name = c_l->lex; }
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
	char* GetName() { return name.get_str(); }
	virtual void print() const ;
	virtual	RPNFunction* Clone() const
	{ 
		return new RPNFunVar(); 
	}
};

/* 						--- Game Functions ---					*/ 

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
/*					--- Game Procedures --- 					*/
class RPNFunBuy: public RPNFunc2
{
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
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
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
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

class RPNFunPrint: public RPNFunction 
{
	RPNElem* EvaluateFun(RPNItem **stack) const
	{
		/* Here should be body */
		return 0;
	}
public:
	RPNFunPrint() {}
	virtual ~RPNFunPrint() {}
	virtual void print() const { printf("[Print]"); }
	virtual	RPNFunction* Clone() const 
	{ 
		return new RPNFunPrint(); 
	}
};

#endif
