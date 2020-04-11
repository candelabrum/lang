#include "rpn_func.hpp"
#include "rpn_fbl.hpp"
#include "rpn_types.hpp"

RPNElem* RPNFunBool::EvaluateFun(RPNItem *stack) const 
{
    RPNBool *bl;
    bool arg1, arg2, res;

    arg1 = PopArgBool(stack);
    arg2 = PopArgBool(stack);
    
    res = EvalOperation(arg1, arg2);
    
    bl = new RPNBool(res);
    
    return bl;
}


