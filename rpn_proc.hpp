#include "rpn.hpp"
#include "rpn_func.hpp"

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
