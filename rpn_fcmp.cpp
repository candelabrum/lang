#include "rpn_fcmp.hpp"
#include "rpn_types.hpp"

RPNElem* RPNFunCmp::EvaluateFun(EvalInfo &eval_info) const
{
    RPNStack *stack = &(eval_info.stack);
    RPNBool *Boolean;
    double arg1, arg2;
    bool res;

    arg2 = PopArgDouble(stack);
    arg1 = PopArgDouble(stack);
    
    res = EvalOperation(arg1, arg2);
    
    Boolean = new RPNBool(res);
    
    return Boolean;
}


