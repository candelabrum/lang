#include <stdio.h>
#include <stdlib.h>
#include "rpn_tv.hpp"

void TableVar::Resize()
{
    couple_var *new_table_var;
	
    if (!table_var)
    {
        table_var = new couple_var[2];
        len = 0;
        max_len = 1;
        return;
    }
    
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

int TableVar::FindCouple(string &var) const
{
	int i = 0;

	while(i < len && !var.is_equal(table_var[i].name_var))
		i++;

    if (i == len)
        return -1;

	return i; 
}

void TableVar::AddVar(string &var)
{
    if (len == max_len)
        Resize();

    len++;
    table_var[len-1].name_var = var;
}

double TableVar::GetValue(string &var)
{
    int index = FindCouple(var);

    if (index == -1)
    {
        AddVar(var);
        index = len - 1;
    }

    return table_var[index].value_var;
}

void TableVar::SetValue(string &var, double value)
{
    int index = FindCouple(var);

    if (index == -1)
    {
        AddVar(var);
        index = len - 1;
    }

    table_var[index].value_var = value;
}
