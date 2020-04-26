#include "l.hpp"

template <>
void list<char**>::free()
{
    node *tmp;
    
    while(head)
    {
        tmp = head;
        head = head->next;
        free_argv(tmp->data);
        delete tmp;
    }
    head = 0;
    end = 0;
}

template <>
void list<char*>::print_data(char* str) const
{
    if (str)
    {
        printf("%s", str);      
        return;
    }
    printf("NULL_STR\n");
}

template <>
void list<int>::print_data(int number) const
{
    printf("%d", number);       
}

template <>
void list<char>::print_data(char symbol) const
{
    printf("%c", symbol);       
}

template <>
void list<char**>::print_data(char** argv) const
{
    if (argv && argv[0])
    {
        printf("%s", argv[0]);
        print_data(argv + 1);
        
        return;
    }
    printf("NULL\n");
}

template<>
void list<lexeme>::delete_nodes(type_lexeme type)
{
    if (!head)
        return;
    
    node **p = &head;

    while(p && *p)  /*maybe here need to call destructor*/
    {
        if (((*p)->data).type == type)
        {
            *p = (*p)->next;
            continue;
        }
        (*p)->next ? p = &((*p)->next) : p = 0;
    }
}
