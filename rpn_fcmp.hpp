#include "rpn_func.hpp"

class RPNFunCmp: public RPNFunc2 
{
public:
    virtual bool EvalOperation(double a1, double a2) const = 0;
    virtual RPNElem* EvaluateFun(EvalInfo &eval_info) const;
};

class RPNFunLess: public RPNFunCmp 
{
public:
	RPNFunLess() {}
	virtual ~RPNFunLess() {}
	virtual void print() const { printf("[<]"); }
	virtual	RPNFunction* Clone() const
	    { return new RPNFunLess(); }
    bool EvalOperation(double a1, double a2) const
        { return a1 < a2; }
};

class RPNFunGreater: public RPNFunCmp 
{
public:
	RPNFunGreater() {}
	virtual ~RPNFunGreater() {}
	bool EvalOperation(double a1, double a2) const
        { return a1 > a2; }

	virtual void print() const { printf("[>]"); }
	virtual	RPNFunction* Clone() const
	    { return new RPNFunGreater(); }
};

class RPNFunLeq: public RPNFunCmp 
{
public:
	RPNFunLeq() {}
	virtual ~RPNFunLeq() {}
	bool EvalOperation(double a1, double a2) const
        { return a1 <= a2; }

	virtual void print() const { printf("[<=]"); }
	virtual	RPNFunction* Clone() const
	    { return new RPNFunLeq();}
};

class RPNFunGeq: public RPNFunCmp 
{
public:
	RPNFunGeq() {}
	virtual ~RPNFunGeq() {}
	RPNElem* EvaluateFun(RPNItem *stack) const
	{
		/* Here should be body */
		return 0;
	}
    bool EvalOperation(double a1, double a2) const
        { return a1 >= a2; }

	virtual void print() const { printf("[>=]"); }
	virtual	RPNFunction* Clone() const
	    { return new RPNFunGeq(); }
};

class RPNFunEqual: public RPNFunCmp 
{
	RPNElem* EvaluateFun(RPNItem *stack) const
	{
		/* Here should be body */
		return 0;
	}
public:
	RPNFunEqual() {}
	virtual ~RPNFunEqual() {}
    bool EvalOperation(double a1, double a2) const
        { return a1 >= a2; }
    virtual void print() const { printf("[=]"); }
	virtual	RPNFunction* Clone() const 
        { return new RPNFunEqual(); }
};
