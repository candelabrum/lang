#include "rpn_list.hpp"

class Executor
{
public:
	void Execute(RPNList &rpn_lst)
	{ 
        EvalInfo eval_info(&(rpn_lst.head)); /* must in private */
        RPNItem *save_head; 
        
        printf("Something executing...");
        save_head = rpn_lst.head;

        while(eval_info.cur_cmd && *(eval_info.cur_cmd))
        {
#ifdef DEBUG_EXE
            printf("\nSTACK\n");
            (eval_info.stack).Print();
#endif
            (*(eval_info.cur_cmd))->elem->Evaluate(eval_info);
        }
        rpn_lst.head = save_head;
	}
};
