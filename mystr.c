#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include "mystr.h"

const char *all_sep[] = {" ", "\n"};

const char *instr[] = {};

enum
{
    len_all_sep = 2
};

enum
{
    chunk_size = 8
};

enum status_str
{
    st_cont_str,
    st_exit_str
};

struct list_of_str
{
    char *str;
    struct list_of_str *next;
};

struct list_of_str* init_list_of_str()
{
     struct list_of_str *lstr;
     lstr = malloc(sizeof(struct list_of_str));
     lstr->next = NULL;
     lstr->str = NULL;
     return lstr;
}

int lenArgV( char **argV)
{
    int i = 0, count = 0;
    while(argV[i] != NULL)
    {
        count++;
        i++;
    }
    return count;
}

static char local_find_char_in(char *str, int search)
{
    int i = 0;
    while(str[i])
    {
        if (str[i] == search)
            return 1;
        i++;
    }
    return 0;
}

int len_of_number(int number)
{
    int count = 0;
    if (number == 0)
        return 1;
    if (number < 0)
        count++;
    while(number)
    {
        count++;
        number = number / 10;
    }
    return count;
}

char* int_to_str(int number)
{
    int i, len;
    char *str;
    len = len_of_number(number);
    str = malloc(len + 1);
    str[len] = 0;
    if (number == 0)
    {
       str[0] = '0';
       return str;
    }
    i = len - 1;
    if (number < 0)
        str[0] = '-';
    number = abs(number);
    while(number)
    {
        str[i] = number % 10 + '0';
        number = number / 10;
        i--;
    }
    return str;
}

void str_move( char *str1, char *str2, int len)
{
    int i;
    for (i = 0; i < len; i++)
        str2[i] = str1[i];
}

char is_number( char *str)
{
    int i = 0;
    while(str[i])
    {
        if ((str[i] > '9') || (str[i] < '0'))
            return 0;
        i++;
    }
    return 1;
}

int str_len( char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return i;
}

char* create_str( char *array, int end_index)
{
    char *res = NULL;
    int i = 0, len = end_index + 1;
    res = malloc(len + 1);
    while(i < len)
    {
        res[i] = array[i];
        i++;
    }
    res[i] = 0;
    return res;
}


int str_to_int( char *str, int *number)
{
    int i = str_len(str) - 1, res = 0, ten = 1;
    if (is_number(str))
    {
        while(i + 1)
        {
            res = res + (str[i] - '0')*ten;
            i--;
            ten = 10*ten;
        }
        *number = res;
        return 0;
    }
    return -1;
}

char str_equal(const char *str1, const char *str2)
{
    enum {not_equal = 0, equal = 1};
    int i = -1;
    if ((str1 && !str2) || (!str1 && str2))
        return not_equal;
    if (str1 == str2)
        return equal;
    do
    {
        i++;
        if (str1[i] != str2[i])
            return not_equal;
    }while((str1[i] != 0) && (str2[i] != 0));
    return equal;
}

char find_char_in( char *str, int len, int search)
{
    int i;
    for(i = 0; i < len; i++)
    {
        if (str[i] == search)
            return i;
    }
    return -1;
}

int len_sep(const char *str, const char **all_sep)
{
    int max_len = 0, i = 0, j = 0;
    for(j = 0; j < len_all_sep; j++)
    {
        i = 0;
        while(str[i] && all_sep[j])
        {
            if (str[i] - all_sep[j][i])
                break;
            i++;

        }
        if (max_len < i)
            max_len = i;
    }
    return max_len;
}

char any_str_equal(const char *str, const char **argV)
{
    int i = 0;
    while(argV[i])
    {
        if (str_equal(argV[i],str))
            return 1;
        i++;
    }
    return 0;
}

int get_index_of_end_word(char *str)
{
    int i = 0;
    char quotes = 0;
    if (str[i] == 0)
        return 0;
    if (len_sep(str, all_sep))
        return len_sep(str, all_sep) - 1;
    while(quotes || (!quotes && !len_sep(str + i, all_sep) && str[i]))
    {
        if (str[i] == '"')
            quotes = (quotes + 1) % 2;
        i++;
    }
    return (i-1);
}

char* del_char(char *str, char* for_del)
{
    int i = 0, j = 0, len = 0;
    char *res = NULL;
    while(str[i])
    {
        if(!local_find_char_in(for_del, str[i]))
            len++;
        i++;
    }
    if (i == len)
        return str;
    i = 0;
    res = malloc(len + 1);
    while(str[i])
    {
        if(!local_find_char_in(for_del, str[i]))
        {
            res[j] = str[i];
            j++;
        }
        i++;
    }
    res[j] = 0;
    free(str);
    return res;
}

void free_lstr(struct list_of_str *lstr)
{
    if (lstr)
    {
        free_lstr(lstr->next);
        if (lstr->str)
            free(lstr->str);
        free(lstr);
    }
}

struct list_of_str* del_last(struct list_of_str *lstr)
{
    if (lstr == NULL)
        return NULL;
    else if (lstr->next == NULL)
    {
        free_lstr(lstr);
        return NULL;
    }
    else if ((lstr->next)->next == NULL)
    {
        lstr->next = del_last(lstr->next);
        return lstr;
    }
    del_last(lstr->next);
    return lstr;
}

char* get_word(char *str, int end_index)
{
    char *res = NULL;
    int i = 0, len = end_index + 1;
    res = malloc(len + 1);
    while(i < len)
    {
        res[i] = str[i];
        i++;
    }
    res[i] = 0;
    return res;
}

void print_lstr(struct list_of_str *lstr)
{
    if (lstr)
    {
        printf("%s",lstr -> str);
/*      putchar('.'); */
        if (lstr->next)
        {
            printf("\n");
        }
        print_lstr(lstr->next);
    }
}

struct list_of_str* transform_str_2_list_of_word(char* str)
{
    struct list_of_str *tmp = NULL, *first_lstr = NULL;
    int  start_index = 0, end_index = 0;
    char  *word = NULL, *empty = " ";
    first_lstr = init_list_of_str();
    tmp = first_lstr;
    do
    {
        end_index = get_index_of_end_word(str + start_index);
        word = get_word(str + start_index, end_index);
		word = del_char(word, "\"");
		if (word[0] && !any_str_equal(word, all_sep))
        {
            tmp->str = word;
            tmp->next = init_list_of_str();
            tmp = tmp->next;
        }
        else if (word[0])
        {
            free(word);
            word = empty;
        }
        start_index = start_index + end_index + 1;
    }while(word[0]);
    free(word);
    first_lstr = del_last(first_lstr);
    return first_lstr;
}

int len_list_of_str(struct list_of_str *lstr)
{
    int count = 0;
    while(lstr)
    {
        count++;
        lstr = lstr->next;
    }
    return count;
}

char* make_new_equal_str(char *str)
{
	int len = str_len(str), i = 0;
	char *new = malloc(len + 1);

	while(str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;

	return new;
}
		
char** transform_lstr_2_argv(struct list_of_str *lstr)
{
    char **res = NULL;
    int i = 0, len = len_list_of_str(lstr);
    res = malloc((len + 1)*sizeof(char*));
    while(lstr && i < len)
    {
        res[i] = make_new_equal_str(lstr->str);
        i++;
        lstr = lstr->next;
    }
    res[i] = NULL;
    return res;
}

char** make_argv(char *str)
{
    struct list_of_str *lstr = NULL;
    char **argv;
    
	lstr = transform_str_2_list_of_word(str);
    argv = transform_lstr_2_argv(lstr);
    free_lstr(lstr); 
	
	return argv;
}
