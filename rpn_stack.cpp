#include "rpn_stack.hpp"

void RPNStack::Push(RPNElem* a_elem) 
{ 
    RPNItem *new_item = new RPNItem(a_elem); 
    
    new_item->next = head;
    head = new_item;
}

RPNElem* RPNStack::Pop() 
{ 
    RPNItem *first_item = head;
    RPNElem *first_elem = head->elem; 

    if (!head)
        return 0;

    head = head->next; 
    delete first_item;

    return first_elem;
} 
