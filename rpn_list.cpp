#ifndef RPN_LIST_H_SENTRY
#define RPN_LIST_H_SENTRY

#include "rpn.hpp"
#include "rpn_list.hpp"

void RPNList::add_node(lexeme *c_l)
{
	RPNConst *elem_const, *new_elem_const;
	RPNFunc2 *elem_func;

	elem_func = TableFunc2.search_by(c_l->type);	
	if (!elem_func)
	{
		add_node_to_end(elem_func);
		return ;
	}
	elem_const = TableConst.search_by(c_l->type);
	new_elem_const = elem_const->Clone();
	new_elem_const.set(c_l->lex);
	add_node_to_end(new_elem_const);


/*	if (!head)
		end = new_node;
	new_node->next = head;
	head = new_node; */
}

void add_node_to_end(RPNElem *elem)
{
	RPNItem *new_RPNItem = new RPNItem(elem); 

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
		(tmp->data).print();
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
		tmp = head;
		head = head->next;
		delete tmp;
	}
	head = 0;
	end = 0;
}


struct couple_rpn_func2
{
	RPNFunc2 *elem;
	type_lexeme type_lex;
};

struct couple_rpn_const
{
	RPNConst *elem;
	type_lexeme type_lex;
};

RPNFunc2* RPNTableFunc2::search_by(type_lexeme t) const
{
	int i = 0;

	while(table[i].type_lex != lex_null && table[i].type_lex != t)
		i++;
	
	return table[i].str;
}

RPNConst* RPNTableConst::search_by(type_lexeme t) const
{
	int i = 0;

	while(table[i].type_lex != lex_null && table[i].type_lex != t)
		i++;
	
	return table[i].str;
}

#endif
