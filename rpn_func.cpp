#include "rpn.hpp"
#include "rpn_func.hpp"
#include "lex.hpp"

void RPNFunction::Evaluate(RPNItem** stack, 
									RPNItem  **cur_cmd) const
{
	RPNElem *res = EvaluateFun(stack);

	if (res)
		Push(stack, res);

	*cur_cmd = (*cur_cmd)->next;
}

RPNElem* static RPNFunction::Convert2RPNElem(lexeme *c_l) const;
{
	RPNFunction *elem_func, *new_elem_function;
	
	if (c_l->type == lex_var)
	{
		RPNFunVar *new_var = new RPNFunVar();

		new_var->set(c_l);
		return new_var;
	}

	elem_func = TableFunc.search_by(c_l->type);	

	if (!elem_func)
		return 0;

	new_elem_func = elem_func->Clone();

	return new_elem_func;
}

void RPNFunVar::print() const 
{ 
	printf("[");
	name.print();
	printf("]");
}

