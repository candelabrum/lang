#include <stdio.h>
#include <stdlib.h>
#include "rpn_var.hpp"
#include "rpn_types.hpp"

RPNElem* RPNFunInd::EvaluateFun(EvalInfo &eval_info) const
{
    RPNFunVar *var;
    double value;
    char *number = new char[size_number]; 
    RPNStack *stack = &(eval_info.stack);

    var = dynamic_cast<RPNFunVar*>(stack->Pop()); 
    if (!var) 
    { 
        printf(" IT IS NOT A VARIABLE\n");
        exit(1);
    }
    value = PopArgDouble(stack);
    sprintf(number, "%fl", value);
    (var->GetName()).concat_ind(number);

    return var;
}

RPNElem* RPNFunAssign::EvaluateFun(EvalInfo &eval_info) const
{	
    RPNFunVar *var;
    double number;
    RPNStack *stack = &(eval_info.stack);

    var = dynamic_cast<RPNFunVar*>(stack->Pop());
    number = PopArgDouble(stack);
    eval_info.tv.SetValue(var->GetName(), number);
    		
    return 0;
}

RPNElem* RPNFunTakeAddr::EvaluateFun(EvalInfo &eval_info) const
{	
    RPNFunVar *var;
    double value;
    RPNDouble *dbl = new RPNDouble();

    var = dynamic_cast<RPNFunVar*>((eval_info.stack).Pop());
    if (!var)
    {
        printf("Expected Var\n");
        exit(1);
    }
    value = eval_info.tv.GetValue(var->GetName());
    dbl->set(value); 

    return dbl;
}
