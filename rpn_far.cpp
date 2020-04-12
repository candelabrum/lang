#include "rpn.hpp"
#include "rpn_far.hpp"
#include "rpn_types.hpp"

RPNElem* RPNFunArithm::EvaluateFun(EvalInfo &eval_info) const
{
    RPNStack *stack = &(eval_info.stack);
    RPNDouble *dbl;
    double arg1, arg2, res;

    arg2 = PopArgDouble(stack);
    arg1 = PopArgDouble(stack);
    
    res = EvalOperation(arg1, arg2);
    
    dbl = new RPNDouble(res);
    
    return dbl;
}


