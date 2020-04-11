/*#include "rpn.hpp"

class RPNList : RPNStack
{
    RPNList(RPNItem *a_head = 0, RPNItem *a_end = 0) 
	{ 
		head = a_head; 
		end = a_end;
	} 
    RPNItem *end;
	void add_node(lexeme *lex);
	void add_node_to_end(RPNElem *elem);
	void disappear() { DeleteStack(); }
	void print() const { PrintStack(); }
	void insert_jmp(RPNItem *old_label, RPNItem *new_label);
	RPNItem* get_head() { return head; }
	RPNItem* get_end() { return end; }
}

class RPNStack
{
public:
    RPNStack(RPNItem a_head = 0) { head = a_head; }
    RPNItem *head;
	bool IsEmpty() const { return GetHead(); }
	void Push(RPNElem* elem); 
   	RPNElem* Pop();
	void PrintStack() const;
	void DeleteStack(); 
};
*/
