#ifndef RPN_FUNC_H_SENTRY
#define RPN_FUNC_H_SENTRY

#include "rpn.hpp"
#include <stdio.h>

class RPNFunction : public RPNElem
{
	virtual RPNElem* EvaluateFun(RPNItem **stack) const = 0;
	void Evaluate(RPNItem** stack, 
								RPNItem  **cur_cmd) const;
};

class RPNFunc2 : public RPNFunction 
{
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
	virtual void print() const { printf("+"); }
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
	virtual void print() const { printf("-"); }
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
	virtual void  print() const { printf("*"); }
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
	virtual void print() const { printf("/"); }
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
	virtual void print() const { printf("<"); }
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
	virtual void print() const { printf(">"); }
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
	virtual void print() const { printf("<="); }
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
	virtual void print() const { printf(">="); }
};



#endif
