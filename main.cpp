#include <stdlib.h>
#include "la.hpp"
#include "sa.hpp"
#include "rpn_list.hpp"
#include "exe.hpp"

class Intepretator 
{
	LexicalAnalyzer la;
	SyntaxAnalyzer sa;
	RPNList rpn_list;
	Executor executor;
public:
	int Run(FILE *f);
};

int Intepretator::Run(FILE *f)
{
	list<lexeme> lst;

	lst = la.start(f);
	if (la.IsErrorNow())
	{
		lst.Delete();
		return 1;
	}
	try
	{
		rpn_list = sa.Start(lst);
	}
	catch(const SAException &ex)
	{
		fprintf(stderr, "%s", ex.GetComment());
		(ex.GetLexeme()).print();
		lst.Delete();
		return 1;
	}
	lst.Delete();
	executor.Execute(rpn_list);
	rpn_list.disappear();

	return 0;
}

int main(int argc, char* const *argv)
{
	Intepretator interpretator;
	FILE *f;
	int res;

	if (argc != 2)
	{
		printf("Wrong parameters\n");
		exit(1);
	}
	f = fopen(argv[1], "r");
	if (!f)
	{
		perror("fopen");
		exit(1);
	}
	res = interpretator.Run(f);
	fclose(f);
	
	return res;
}
