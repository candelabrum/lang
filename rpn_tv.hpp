#include "str.hpp"
#include "lex.hpp"

struct couple_var
{
    couple_var : name_var() (double value = 0) 
        { value_var = value; }
    string name_var;
    double value_var;
};

class TableVar
{
    int len;
    int max_len;
    couple_var *table_var;
    void Resize();
    unsigned int FindCouple(string &var) const;
public:
    TableVar (couple_var *a_table_var = 0) 
        { table_var = a_table_var; }
    void AddVar(string &var);
    double GetValue(string &var);
    double SetValue(string &var);
};
