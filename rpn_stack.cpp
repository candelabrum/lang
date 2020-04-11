void RPNStack::Push(RPNElem* elem) 
{ 
    RPNItem *new_item= new RPNItem(elem); 

    if (!head)
	    end = new_item;
    new_item->next = head;
	head = new_item;
}

