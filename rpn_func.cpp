#include "rpn.hpp"
#include "rpn_func.hpp"

void RPNFunction::Evaluate(RPNItem** stack, 
									RPNItem  **cur_cmd) const
{
	RPNElem *res = EvaluateFun(stack);

	if (res)
		Push(stack, res);

	*cur_cmd = (*cur_cmd)->next;
}
