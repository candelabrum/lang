#include "la.hpp"
#include "sa.hpp"
#include "rpn_list.hpp"
#include "exe.hpp"

class Interpretator 
{
    LexicalAnalyzer la;
    SyntaxAnalyzer sa;
    RPNList rpn_list;
    Executor executor;
  /*int Init(const char *file); */
public:
    int Run(FILE* f, Game *game);
};
