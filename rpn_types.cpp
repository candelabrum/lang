#include "mystr.h"
#include "rpn_types.hpp"

class RPNTableConst
{
    struct couple_rpn_const
    {
        RPNConst *elem;
        type_lexeme type_lex;
    };

    RPNDouble Number, *number = &Number;
    RPNStringLiteral StrLit, *strlit = &StrLit;
    RPNBool Boolean, *boolean = &Boolean;

    couple_rpn_const table[5]{
        {number, lex_fractional},
        {number, lex_integ},
        {strlit, lex_strlit},
        {boolean, lex_bool},
        {0, lex_null}
    };

public:
    RPNConst* search_by(type_lexeme type) const;
    /* There should have been a binary search here */
};

RPNConst* RPNTableConst::search_by(type_lexeme t) const
{
    int i = 0;

    while(table[i].type_lex != lex_null && table[i].type_lex != t)
        i++;
    
    return table[i].elem;
}

RPNElem* RPNConst::Convert2RPNElem(lexeme *c_l) const 
{
    static RPNTableConst TableConst; /*???*/
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
    double res;

    sscanf(str, "%lf", &res);
//  printf("%s VALUE %d\n", str, res);
    value = res;

    delete [] str;
}

void RPNConst::Evaluate(EvalInfo &eval_info) const
{
    (eval_info.stack).Push(Clone());
    eval_info.next_cmd();
    /*eval_info.cur_cmd = cur_cmd;*/
}
