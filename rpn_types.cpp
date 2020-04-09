#include "rpn_types.hpp"

static RPNElem* RPNConst::Convert2RPNElem(lexeme *c_l) const 
{
	RPNConst *elem_const, *new_elem_const;

	elem_const = TableConst.search_by(c_l->type);
	if (!elem_const)
		return 0;
	new_elem_const = elem_const->Clone();
	new_elem_const->set(c_l->lex);

	return new_elem_const;
}



void RPNDouble::set(string& number)
{ 
	char *str = number.get_str();
	int res;

	str_to_int(str, &res);
//	printf("%s VALUE %d\n", str, res);
	value = (double)res;

	delete [] str;
}

void RPNConst::Evaluate(RPNItem **stack, RPNItem **cur_cmd) const
{
	Push(stack, Clone());
	*cur_cmd = (*cur_cmd)->next;
}
