#include "str.hpp"
#include "lex.hpp"
#include <stdio.h>

struct couple_var
{
    string name_var;
    double value_var;
    couple_var (double value = 0) : name_var() 
        { value_var = value; }
    void print() const
    {
        printf(" Name Var | Value Var \n");
        name_var.print();
        printf("    %fl\n", value_var);
    }
};

class TableVar
{
    int len;
    int max_len;
    couple_var *table_var;
    void Resize();
    int FindCouple(string &var) const;
public:
    TableVar (couple_var *a_table_var = 0) 
    { 
        table_var = a_table_var;
        len = 0;
        max_len = 0;
    }
    void AddVar(string &var);
    double GetValue(string &var);
    void SetValue(string &var, double value);
    void print() const
    {
        int i = 0;

        while(i < len)
        {
            table_var[i].print();
            i++;
        }
    }
    ~TableVar() { delete [] table_var; }
};
