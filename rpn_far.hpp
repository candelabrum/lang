#include "rpn.hpp"
#include "rpn_func.hpp"

class RPNFunArithm : public RPNFunc2 /* RPNDDDOp more better */
{
public:
    virtual double EvalOperation(double a1, double a2) const = 0;
    virtual RPNElem* EvaluateFun(RPNItem *stack) const;
};

class RPNFunPlus : public RPNFunArithm
{
public:

    RPNFunPlus() {}
	virtual ~RPNFunPlus() {}
	virtual double EvalOperation(double a1, double a2) const
        { return a1 + a2; }
    virtual void print() const { printf("[+]"); }
	virtual	RPNFunction* Clone() const { return new RPNFunPlus(); }
};

class RPNFunMinus : public RPNFunArithm
{
public:
	RPNFunMinus() {}
	virtual ~RPNFunMinus() {}
	double EvalOperation(double a1, double a2) const
        { return a1 - a2; }
	virtual	RPNFunction* Clone() const 
        { return new RPNFunMinus(); }
	virtual void print() const { printf("[-]"); }
};

class RPNFunMultiply : public RPNFunArithm
{
public:
	RPNFunMultiply() {}
	virtual ~RPNFunMultiply() {}
	double EvalOperation(double a1, double a2) const
        { return a1 * a2; }
	virtual void  print() const { printf("[*]"); }
	virtual	RPNFunction* Clone() const 
	    { return new RPNFunMultiply(); }
};

class RPNFunDivision : public RPNFunArithm
{
public:
	RPNFunDivision() {}
	virtual ~RPNFunDivision() {}
	double EvalOperation(double a1, double a2) const
        { return a1 / a2; }
	virtual void print() const { printf("[/]"); }
	virtual	RPNFunction* Clone() const
	    { return new RPNFunDivision(); }
};
