#include <stdio.h>
#include "rpn.hpp"
#include "rpn_func.hpp"

class RPNFunInd : public RPNFunc2
{
    enum
    {
        size_number = 16
    };

    RPNElem* EvaluateFun(EvalInfo &eval_info) const;

public:
	RPNFunInd() {}
	virtual ~RPNFunInd() {}
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
	RPNElem* EvaluateFun(EvalInfo &eval_info) const;
	virtual void print() const { printf("[:=]");}
	virtual	RPNFunction* Clone() const
	    { return new RPNFunAssign(); }
};

class RPNFunTakeAddr: public RPNFunc1
{
public:
	RPNFunTakeAddr() {}
	virtual ~RPNFunTakeAddr() {}
	RPNElem* EvaluateFun(EvalInfo &eval_info) const;
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
	RPNElem* EvaluateFun(EvalInfo &eval_info) const { return 0; }
	string& GetName() { return name; }
	virtual void print() const;
	virtual	RPNFunction* Clone() const
	{ 
		return new RPNFunVar(); 
	}
};
