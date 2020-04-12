#include "str.hpp"
#include "lex.hpp"

struct couple_var
{
    string name_var;
    double value_var;
    couple_var (double value = 0) : name_var() 
        { value_var = value; }

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
    { 
        table_var = a_table_var;
        len = 0;
        max_len = 0;
    }
    void AddVar(string &var);
    double GetValue(string &var);
    void SetValue(string &var, double value);
};
