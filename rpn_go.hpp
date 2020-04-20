#ifndef RPN_GO_H_SENTRY
#define RPN_GO_H_SENTRY

#include <stdio.h>
#include "rpn_func.hpp"
#include "rpn_types.hpp"

class RPNOp : public RPNFunction 
{
public: 
	virtual RPNElem* EvaluateFun(EvalInfo &eval_info) const
		{ return 0; }

	virtual RPNOp* Clone() const = 0;
/*	RPNElem* Convert2RPNElem(lexeme *c_l) const; */
	RPNItem* PopArgLabel(RPNStack *stack) const;
};

class RPNOpGo : public RPNOp
{
public:
	virtual RPNOpGo* Clone() const 
		{ return new RPNOpGo(); }
/*	virtual ~RPNOpGo() {};*/
	virtual void print() const { printf("OpGo"); }
	void Evaluate(EvalInfo &eval_info) const 
	{
		RPNItem *label;

		label = PopArgLabel(&eval_info.stack);
		
		eval_info.cur_cmd = &(label);

//		delete label; /* ? */
	}
};

class RPNOpGoFalse: public RPNOp
{
public:
/*	virtual ~RPNOpGoFalse() {};*/
	virtual RPNOpGoFalse* Clone() const 
		{ return new RPNOpGoFalse(); }
	virtual void print() const { printf("OpGoFalse"); }
	void Evaluate(EvalInfo &eval_info) const 
	{
		RPNItem *label;
		bool bl;

		bl = PopArgBool(&eval_info.stack);
		label = PopArgLabel(&eval_info.stack);
		
		if (!bl)
			eval_info.cur_cmd = &(label);

//		delete bl; /* ? */
//		delete label; /* ? */
	}
};

class RPNNoop : public RPNOp
{
	
	virtual void Evaluate(EvalInfo &eval_info) const {}
public:
/*	virtual ~RPNNoop(){};*/
	virtual RPNNoop* Clone() const 
		{ return new RPNNoop(); }

	void print() const { printf("Noop"); }
};

#endif
