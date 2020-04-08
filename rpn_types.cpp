
#include "rpn_types.hpp"

void RPNDouble::set(string& number)
{ 
	char *str = number.get_str();
	int res;

	str_to_int(str, &res);
//	printf("%s VALUE %d\n", str, res);
	value = (double)res;

	delete str;
}

void RPNConst::Evaluate(RPNItem **stack, RPNItem **cur_cmd) const
{
	Push(stack, Clone());
	*cur_cmd = (*cur_cmd)->next;
}
