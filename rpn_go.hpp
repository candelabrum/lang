#ifndef RPN_GO_H_SENTRY
#define RPN_GO_H_SENTRY

#include <stdio.h>
#include "rpn_func.hpp"
#include "rpn_types.hpp"

class RPNOp : public RPNFunction 
{
public: 
	virtual RPNElem* EvaluateFun(EvalInfo &eval_info) const = 0;

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
	virtual RPNElem* EvaluateFun(EvalInfo &eval_info) const 
	{
		RPNItem *label;

		label = PopArgLabel(&eval_info.stack);
		
		eval_info.cur_cmd = &(label);

//		delete label; /* ? */

		return 0;
	}
};

class RPNOpGoFalse: public RPNOp
{
public:
/*	virtual ~RPNOpGoFalse() {};*/
	virtual RPNOpGoFalse* Clone() const 
		{ return new RPNOpGoFalse(); }
	virtual void print() const { printf("OpGoFalse"); }
	virtual RPNElem* EvaluateFun(EvalInfo &eval_info) const 
	{
		RPNItem *label;
		bool bl;

		label = PopArgLabel(&eval_info.stack);
		bl = PopArgBool(&eval_info.stack);

		if (!bl)
			eval_info.cur_cmd = &(label);

//		delete bl; /* ? */
//		delete label; /* ? */
	
		return 0;
	}
};

class RPNNoop : public RPNOp
{
	
	virtual RPNElem* EvaluateFun(EvalInfo &eval_info) const 
		{ return 0; }
public:
/*	virtual ~RPNNoop(){};*/
	virtual RPNNoop* Clone() const 
		{ return new RPNNoop(); }

	void print() const { printf("Noop"); }
};

#endif
