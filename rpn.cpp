#include <stdio.h>
#include "rpn.hpp"

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

void RPNItem::Print() const
{
	RPNItem *tmp = next;
    
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
