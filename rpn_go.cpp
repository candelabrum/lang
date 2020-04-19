#include "rpn.hpp"
#include "lex.hpp"
#include "rpn_go.hpp"

class RPNTableOp
{
	struct couple_rpn_op
	{
		RPNOp *elem;
		type_lexeme type_lex;
	};

	RPNOpGo OpGo, *op_go = &OpGo;
	RPNOpGoFalse OpGoFalse, *op_go_false = &OpGoFalse;
	RPNNoop Noop, *noop = &Noop;

	couple_rpn_op table[4] {
		{op_go, lex_op_go},
		{op_go_false, lex_op_go_false},
		{noop, lex_noop},
		{0, lex_null}
	};

public:
	RPNOp* search_by(type_lexeme type) const;
	/* There should have been a binary search here */
};

RPNOp* RPNTableOp::search_by(type_lexeme t) const
{
	int i = 0;

	while(table[i].type_lex != lex_null && table[i].type_lex != t)
		i++;
	
	return table[i].elem;
}

RPNElem* RPNOp::Convert2RPNElem(lexeme *c_l) const
{
	static RPNTableOp TableOp;
	RPNOp *elem_op, *new_elem_op;

	elem_op = TableOp.search_by(c_l->type);

	if (!elem_op)
		return 0;

	new_elem_op = elem_op->Clone();

	return new_elem_op;
}

RPNElem* RPNOp::PopArgLabel(RPNStack *stack) const
{
    RPNLabel *label;
    RPNElem *res;

    label = dynamic_cast<RPNLabel*>(stack->Pop());
    if (!label)
    {
        fprintf(stderr, "GOOD BYE: IN FUNC2 has not BOOL\n");
        exit(1);
    }
    
    res = label->Get();
    delete label;

    return res;
}

