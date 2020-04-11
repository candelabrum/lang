#include "rpn.hpp"
#include "rpn_list.hpp"

class RPNStack : private RPNList 
{
public:
	bool IsEmpty() const { return GetHead(); }
	void Push(RPNElem* elem); 
   	RPNElem* Pop() 
    { 
        RPNItem *first_item = GetHead();
        RPNElem *first = (GetHead())->elem;

        head = head->next;
        delete first_item();
        
        return GetHead();
    } 

	void PrintStack() const { print(); }
	void DeleteStack() { disappear(); }
};

struct EvalInfo
{
    RPNItem **cur_cmd;
    RPNStack Stack;
};

