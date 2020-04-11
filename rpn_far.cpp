#include "rpn.hpp"
#include "rpn_far.hpp"
#include "rpn_types.hpp"

RPNElem* RPNFunArithm::EvaluateFun(RPNItem *stack) const
{
    RPNDouble *dbl;
    double arg1, arg2, res;

    arg1 = PopArgDouble(stack);
    arg2 = PopArgDouble(stack);
    
    res = EvalOperation(arg1, arg2);
    
    dbl = new RPNDouble(res);
    
    return dbl;
}


