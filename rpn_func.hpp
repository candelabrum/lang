#ifndef RPN_FUNC_H_SENTRY
#define RPN_FUNC_H_SENTRY

#include "rpn.hpp"
#include <stdio.h>

class RPNFunction : public RPNElem
{
	virtual RPNElem* EvaluateFun(RPNItem **stack) const = 0;
	void Evaluate(RPNItem** stack, 
								RPNItem  **cur_cmd) const;
public:
	virtual ~RPNFunction() {};
};

class RPNFunc2 : public RPNFunction 
{
public:
	virtual	RPNFunc2* Clone() const = 0;
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
	virtual	RPNFunc2* Clone() const { return new RPNFunPlus(); }
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
	virtual	RPNFunc2* Clone() const { return new RPNFunMinus(); }

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
	virtual	RPNFunc2* Clone() const 
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
	virtual	RPNFunc2* Clone() const
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
	virtual	RPNFunc2* Clone() const
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
	virtual	RPNFunc2* Clone() const
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
	virtual	RPNFunc2* Clone() const
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
	virtual	RPNFunc2* Clone() const
	{ 
		return new RPNFunGeq(); 
	}
};

#endif
