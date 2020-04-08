#ifndef RPN_FUNC_H_SENTRY
#define RPN_FUNC_H_SENTRY

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

#endif
