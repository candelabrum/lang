#ifndef RPN_H_SENTRY
#define RPN_H_SENTRY

#include "lex.hpp"
#include "rpn_tv.hpp"
#include "first_step/game.hpp"

struct RPNItem;

struct EvalInfo;

class RPNElem
{
public:
	virtual ~RPNElem() {};
	virtual void Evaluate(EvalInfo &eval_info) const = 0;
	virtual void print() const = 0;
	virtual RPNElem* Convert2RPNElem(lexeme *l) const = 0;

/*protected:
	static void Push(RPNItem *stack, RPNElem *elem) {} 
	static RPNElem* Pop(RPNItem *stack) { return 0; } */
};

struct RPNItem
{
    RPNItem(RPNElem *a_elem = 0, RPNItem *a_next = 0) 
    { 
        elem = a_elem; 
        next = a_next; 
    }
/*	bool IsEmpty() const { return !(next || elem); } */
	void Print() const;
    void Disappear();

    RPNElem *elem;
    RPNItem *next;

/*	RPNItem(RPNElem *a_elem) { elem = a_elem; next = 0;} */
	void delete_elem();
};

class RPNStack
{
public:
    RPNStack (RPNItem *a_head = 0) { head = a_head; }
    RPNItem *head;
    void Push(RPNElem* elem); 
   	RPNElem* Pop();
    bool IsEmpty() { return !head; }
    void Print() const 
    { 
        if (head)
            head->Print();
    }

	void Disappear()
    {
        if (head)
            head->Disappear();
    }

};

struct EvalInfo
{
    EvalInfo(RPNItem *a_cur_cmd, Game *a_game)
    {	
		cur_cmd = a_cur_cmd;
		game = a_game;
	}

    RPNItem *cur_cmd;
    RPNStack stack;
    TableVar tv;
    Game *game;

    ~EvalInfo() { stack.Disappear(); }
    void next_cmd()
    {
		cur_cmd = cur_cmd->next;
    }
};

#endif
