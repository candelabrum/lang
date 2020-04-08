#include "rpn.hpp"
#include "rpn_types.hpp"
#include "rpn_func.hpp"

struct RPNList
{
	RPNList(RPNItem *a_head = 0, RPNItem *a_end = 0) 
	{ 
		head = a_head; 
		end = a_end;
	} 
	RPNItem *head;
	RPNItem *end;
	void add_node(lexeme *lex);
	void add_node_to_end(RPNElem *elem);
	void disappear();
	void print() const;
};

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

class RPNTableFunc2
{
	couple_rpn_func2 *table;	
public:
	RPNTableFunc2(couple_rpn_func2 *a_table = 0) { table = a_table; } 
	RPNFunc2* search_by(type_lexeme type) const;
	/* There should have been a binary search here */
};

class RPNTableConst
{
	couple_rpn_const *table;	
public:
	RPNTableConst(couple_rpn_const *a_table = 0)
	{
		table = a_table; 
	}
	RPNConst* search_by(type_lexeme type) const;
	/* There should have been a binary search here */
};

class RPNNoop : public RPNElem
{
public:
	virtual ~RPNNoop(){};
	virtual void Evaluate(RPNItem **stack,
						RPNItem **cur_cmd) const {}
	void print() const { printf("Noop"); }
}noop, *rpn_noop = &noop;


