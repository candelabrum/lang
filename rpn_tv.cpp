#include "rpn_tv.hpp"

void TableVar::Resize()
{
    char *new_table_var;
	
    new_table_var = new couple_var[2*len + 1];
	max_len = 2*len;

	if (table_var)
    {
        for(int i = 0; i < len; i++)
            new_table_var[i] = table_var[i];
    }

	delete[] table_var;
	table_var = new_table_var;
}

unsigned int FindCouple(string &var) const
{
	int i = 0;

	while(i < len && !var.is_equal(table[i].str))
		i++;
	
    if (i == len)
    {
        printf("HELLO Exit from TalbeVar\n");
        exit(1);
    }

	return i; 
}

void TableVar::AddVar(string &var)
{
    if (len == max_len)
        Resize();

    len++;
    table_var[len].name_var = var;
}

double GetValue(string &var)
{
   int index = FindCouple(var);

   return table_var[index].value_var;
}

void SetValue(string var, double value)
{
    int index = FindCouple(var);

    table_var[index].value_var = value;
}