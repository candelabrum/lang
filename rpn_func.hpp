#ifndef RPN_FUNC_H_SENTRY
#define RPN_FUNC_H_SENTRY

#include "rpn.hpp"
#include "lex.hpp"
#include <stdio.h>

class RPNFunction : public RPNElem
{
    virtual RPNElem* EvaluateFun(EvalInfo &eval_info) const = 0;
    void Evaluate(EvalInfo &eval_info) const;
public:
    double PopArgDouble(RPNStack * eval_info) const;
    bool PopArgBool(RPNStack * eval_info) const;
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

/* 						--- Game Functions ---					*/ 

class RPNFunPrint : public RPNFunction 
{
	RPNElem* EvaluateFun(EvalInfo &eval_info) const;
public:
	RPNFunPrint() {}
	virtual ~RPNFunPrint() {}
	virtual void print() const { printf("[Print]"); }
	virtual	RPNFunction* Clone() const 
	    { return new RPNFunPrint(); }
};

#endif
