#ifndef RPN_FBL_H_SENTRY
#define RPN_FBL_H_SENTRY

#include "rpn_func.hpp"
#include "rpn_types.hpp"

class RPNFunBool : public RPNFunc2 
{
public:
    virtual bool EvalOperation(bool a1, bool a2) const = 0;
    virtual RPNElem* EvaluateFun(EvalInfo &eval_info) const;
};

class RPNFunOr: public RPNFunBool
{
public:
    RPNFunOr() {}
    virtual ~RPNFunOr() {}
    virtual void print() const { printf("[|]"); }
    bool EvalOperation(bool a1, bool a2) const
        { return a1 || a2; }
    virtual RPNFunction* Clone() const { return new RPNFunOr();}
};

class RPNFunAnd: public RPNFunBool
{
public:
    RPNFunAnd() {}
    virtual ~RPNFunAnd() {}
    virtual void print() const { printf("[&]"); }
    bool EvalOperation(bool a1, bool a2) const
        { return a1 && a2; }
    virtual RPNFunction* Clone() const { return new RPNFunAnd();}
};

class RPNFunNot: public RPNFunc1
{
    RPNElem* EvaluateFun(EvalInfo &eval_info) const
    {
        RPNBool *bl;
        bool arg, res;

        arg = PopArgBool(&(eval_info.stack));
        res = EvalOperation(arg);
        bl = new RPNBool(res);
    
        return bl;
    }
public:
    RPNFunNot() {}
    virtual ~RPNFunNot() {}
    virtual void print() const { printf("[!]"); }
    bool EvalOperation(bool a1) const
        { return !a1; }
    virtual RPNFunction* Clone() const 
        { return new RPNFunNot(); }
};

#endif
