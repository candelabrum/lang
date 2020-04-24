#include <stdlib.h>
#include "interp.hpp"

int Interpretator::Run(FILE *f, Game *game)
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
	executor.Execute(rpn_list, game);
	rpn_list.disappear();

	return 0;
}

/*int Interpretator::Init(const char *file)
{
	FILE *f;
	int res;

	f = fopen(file, "r");
	if (!f)
	    return 0;
	fclose(f);
	
	return res;
}*/
