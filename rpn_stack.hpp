#include "rpn_item.hpp"

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
