#include "rpn_func.hpp"
#include "rpn_fbl.hpp"
#include "rpn_types.hpp"

RPNElem* RPNFunBool::EvaluateFun(EvalInfo &eval_info) const 
{
    RPNBool *bl;
    bool arg1, arg2, res;
    RPNStack *stack = &(eval_info.stack);

    arg2 = PopArgBool(stack);
    arg1 = PopArgBool(stack);
    
    res = EvalOperation(arg1, arg2);
    
    bl = new RPNBool(res);
    
    return bl;
}


