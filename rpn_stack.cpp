#include "rpn.hpp"

void RPNStack::Push(RPNElem* elem) 
{ 
    RPNItem *new_item = new RPNItem(elem); 

    new_item->next = head;
	head = new_item;
}

RPNElem* RPNStack::Pop() 
{ 
    RPNItem *first_item = head;
    RPNElem *first = head->elem;

    head = head->next;
    delete first_item();
        
    return head;
} 

void RPNStack::PrintStack() const
{
	RPNItem *tmp = head;
	
	while(tmp)
	{
		(tmp->elem)->print();
		printf("->");
		tmp = tmp->next;
	}
}

void RPNStack::DeleteStack()
{
	RPNItem *tmp;
	
	if (head)
		printf("DESTRUCTOR\n");
	while(head)
	{
		printf("\nKILL!\n");
		tmp = head;
		head = head->next;
        tmp.delete_elem();
		delete tmp;
	}
	head = 0;
	end = 0;
}
