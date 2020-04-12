#include "rpn_fcmp.hpp"
#include "rpn_types.hpp"

RPNElem* RPNFunCmp::EvaluateFun(RPNStack *stack) const
{
    RPNBool *Boolean;
    double arg1, arg2;
    bool res;

    arg2 = PopArgDouble(stack);
    arg1 = PopArgDouble(stack);
    
    res = EvalOperation(arg1, arg2);
    
    Boolean = new RPNBool(res);
    
    return Boolean;
}


