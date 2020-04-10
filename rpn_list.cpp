#include "rpn.hpp"
#include "rpn_list.hpp"
#include "rpn_func.hpp"
#include "rpn_types.hpp"
#include "rpn_go.hpp"
#include "lex.hpp"

void RPNList::add_node(lexeme *c_l)
{
	RPNElem *new_elem;
	
	for(int i = 0; i < 3; i++)
	{
		new_elem = intermediate_classes[i]->Convert2RPNElem(c_l);
		if (new_elem)
			break;
	}
	add_node_to_end(new_elem);
}

void RPNList::insert_jmp(RPNItem *jump_label,
									RPNItem *place_label)
{
	RPNLabel *new_label = new RPNLabel(place_label);

	delete jump_label->elem;

	jump_label->elem = new_label;
}

void RPNList::add_node_to_end(RPNElem *elem)
{
	RPNItem *new_item = new RPNItem(elem); 

	if (end)
	{
		end->next = new_item;
		end = end->next;
		return;
	}
	head = new_item;
	end = new_item;
}

void RPNList::print() const
{
	RPNItem *tmp = head;
	
	while(tmp)
	{
		(tmp->elem)->print();
		printf("->");
		tmp = tmp->next;
	}
}

void RPNList::disappear()
{
	RPNItem *tmp;
	
	if (head)
		printf("DESTRUCTOR\n");
	while(head)
	{
		printf("\nKILL!\n");
		tmp = head;
		head = head->next;
		delete tmp;
	}
	head = 0;
	end = 0;
}
