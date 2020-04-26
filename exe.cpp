#include "exe.hpp"

void Executor::Execute(RPNList &rpn_lst, Game *game)
{ 
	RPNItem *save_head; 
        
	EvalInfo eval_info(rpn_lst.head, game);
    save_head = rpn_lst.head;

    while(eval_info.cur_cmd)
    {
#ifdef DEBUG_EXE
		printf("\nSTACK\n");
        (eval_info.stack).Print();
        printf("\nTABLE VAR\n");
        eval_info.tv.print();
		printf("\nELEM\n");
		eval_info.cur_cmd->elem->print();
		printf("\n");
#endif
		try 
		{
        	eval_info.cur_cmd->elem->Evaluate(eval_info);
		}
		catch(const ExceptionDivideZero &ex)
		{
			printf("Division by zero\n");
			eval_info.cur_cmd = 0;
		}
    }
    rpn_lst.head = save_head;
}
