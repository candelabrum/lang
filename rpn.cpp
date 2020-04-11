#include <stdio.h>
#include "rpn.hpp"

void RPNItem::Push(RPNElem* a_elem) 
{ 
    if (elem)
    {
        RPNItem *new_item = new RPNItem(elem); 
    
        new_item->next = next;
	    next = new_item;

        return;
    }
    elem = a_elem;
}

RPNElem* RPNItem::Pop() 
{ 
    RPNElem *first_elem;
    
    if (next)
    {
        RPNItem **first_item = &next;
        
        first_elem = next->elem;
        *first_item = (*first_item)->next;
        delete *first_item;
        
        return first_elem;
    }
    
    first_elem = elem;
    elem = 0;

    return first_elem;
} 

void RPNItem::Print() const
{
	RPNItem *tmp = next;

    if (elem)
        elem->print();
    printf("->");
	while(tmp)
	{
		(tmp->elem)->print();
		printf("->");
		tmp = tmp->next;
	}
}

void RPNItem::Disappear()
{
	RPNItem *tmp;
	
	if (next)
		printf("DESTRUCTOR\n");
	while(next)
	{
		printf("\nKILL!\n");
		tmp = next;
		next = next->next;
        tmp->delete_elem();
		delete tmp;
	}
    delete_elem();
	next = 0;
    delete this;
}

void RPNItem::delete_elem()
{
	if (elem)
    {
        delete elem; 
    	elem = 0;
    }
}
