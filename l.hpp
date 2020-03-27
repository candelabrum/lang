#ifndef LIST_H_SENTRY
#define LIST_H_SENTRY

#include "string.h"
#include <stdio.h>
#include <string.h>
#include "str.hpp"
#include "lex.hpp"

template <class T>
class list
{
private:
	struct node
	{
		T data;
		node *next;
	public:
		node(T& a_data);
	};

	void print_data(T data) const;
	void my_print_reverse(node *a_head);
//	const list<T>& operator=(const list<T>& lst);
	/* don't copy it! */

	node *head, *end;
public:
	list (node *a_head = 0){ head = a_head; end = a_head; };
	void print();
	void add_node(T& a_data);
	void add_node_cp(T a_data);
	void delete_nodes(type_lexeme type);
	T* get_node(unsigned int index) const;
	T& get_data(unsigned int index);
	void next();
	void make_null();
	int get_len() const;
	void print_reverse();
	bool is_empty();
	void add_node_to_end(T& a_data);
	~list();
};

template <class T>
void list<T>::make_null()
{
	head = 0;
	end = 0;
}

template <class T>
bool list<T>::is_empty()
{
	return !head;
}

template <class T>
void list<T>::next()
{
	node *tmp = head;

	if (head)
	{
		head = head->next;
		delete tmp;
	}
	if (!head)
		end = 0;
}

template <class T>
void list<T>::add_node_to_end(T& a_data)
{
	node *new_node = new node(a_data); 

	if (end)
	{
		end->next = new_node;
		end = end->next;
		return;
	}
	head = new_node;
	end = new_node;
}

template <class T>
T* list<T>::get_node(unsigned int index) const
{
	node *tmp = head;
	unsigned int i = 0;

	while(tmp && i < index)
		tmp = tmp->next;

	if (i == index)
		return &(tmp->data);
	
	return 0;
}

template <class T>
void list<T>::delete_nodes(type_lexeme t)
{}

template <class T>
T& list<T>::get_data(unsigned int index)
{
	if (get_node(index))
		return *get_node(index);
	
	return *get_node(0);
}

template <class T>
list<T>::~list()
{
	node *tmp;
	
//	printf("DESTRUCTOR\n");
	while(head)
	{
		tmp = head;
		head = head->next;
		delete tmp;
	}
	head = 0;
	end = 0;
}

template <class T>
void list<T>::print_data(T data) const
{
	data.print();
}

template <class T>
list<T>::node::node(T& a_data)
{
	data = a_data;
	next = 0;
}

template <class T>
int list<T>::get_len() const
{
	node *tmp = head;
	int len = 0;
	
	while(tmp)
	{
		len++;
		tmp = tmp->next;
	}

	return len;
}

template <class T>
void list<T>::add_node(T& a_data)
{
	node *new_node = new node(a_data); /* why here copying str */

	if (!head)
		end = new_node;
	new_node->next = head;
	head = new_node;
//	head->data = a_data; /* but here not copying str */
}

template <class T>
void list<T>::add_node_cp(T a_data)
{
	node *new_node = new node(a_data); /* why here copying str */

	if (!head)
		end = new_node;
	new_node->next = head;
	head = new_node;
//	head->data = a_data; /* but here not copying str */
}

template <class T>
void list<T>::print() 
{
	node *tmp = head;
	
	while(tmp)
	{
//		(tmp->data).print();
//		printf("->");
		print_data(tmp->data);
		tmp = tmp->next;
	}
//	printf("NULL\n");
}

template <class T>
void list<T>::my_print_reverse(node *first)
{
	if (first)
	{
		my_print_reverse(first->next);
		print_data(first->data);
	//	printf("->");
		return;
	}
	printf("NULL\n");
}

template <class T>
void list<T>::print_reverse()
{
	my_print_reverse(head);
}

#endif 
