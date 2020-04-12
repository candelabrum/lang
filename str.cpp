#include <stdio.h>
#include <string.h>
#include "string.h"
#include "str.hpp"

/* make more good name for is_balanced */
bool string::is_equal(const char *a_str) const
{
	return str_equal(str, a_str);
}

bool string::is_equal(string &a_str) const
{
    return a_str.is_equal(str);
}

const string& string::operator=(const string& s)
{
	str = s.get_str();
	len = s.get_len();
	max_len = len;
//	printf("IT WAS OPERATOR= %s\n", str);
	
	return *this;
}

int string::is_balanced_by(char open, char close) const
{
	int count = 0;
	
	for(int i = 0; i < len; i++)
	{
		if (str[i] == open)
			count++;
		if (str[i] == close)
			count--;
	}

	return count;
}

string::~string()
{
//	printf("IT WAS DESTRUCTOR: ");
//	for(int i = 0; i < len; i++)
//		putchar(str[i]);
//	printf(":\n");	
	delete [] str;
}

void string::print() const
{
	printf("%s", str);
}

void string::print_f() const
{
	printf("[%20.19s]", str);
}


string::string(const char *a_str)
{
	if (!a_str)
	{
		max_len = 0;
		len = 0;
		str = 0;
		return;
	}
	len = strlen(a_str);
	max_len = len;
	str = new char[len + 1];
	str[len] = 0;
	strcpy(str, a_str);
}

string::string(const string &s)
{
	str = s.get_str();
	len = s.get_len();
	max_len = len;
//	printf("IT WAS COPYING %s\n", str);
}

void string::set(const char *a_str)
{
	len = strlen(a_str);
	max_len = len;
	str = new char[len + 1];
	str[len] = 0;
	strcpy(str, a_str);
}

char** string::MakeArgv()
{
	return make_argv(str);
}

char* string::get_str() const
{
	if (str)
	{
		char *cp_str = new char[len + 1];

		memmove(cp_str, str, len + 1);
		cp_str[len] = 0;

		return cp_str;
	}
	
	return 0;
}

char& string::operator[](int index)
{
	return str[index];
}

char string::any_str_equal(const char **argv) const
{
	return ::any_str_equal(str, argv);
}

void string::set(char *a_str, int a_len) 
{
	len = a_len;
	max_len = a_len;
	str = new char[len + 1];
	memmove(str, a_str, a_len);
	str[a_len] = 0;
}
	
void string::add_to_len(int number)
{
	char *new_str;
	
	len += number;
	if (len <= max_len)
	{
		str[len] = 0;
		return;
	}
	new_str = new char[2*len + 1];
	max_len = 2*len;
	new_str[len] = 0;
	if (str)
		memmove(new_str, str, len - number + 1);
	
	delete[] str;
	str = new_str;
}

char string::have_sys_line(char symbol) const
{
	char *p_index, *res;
	int dif, index;
	

	p_index = (char*)memchr(str, symbol, len);
	dif = p_index - str;
	if (!p_index)
		return 0;
	res = (char*)memchr(str + dif, '\n', len - dif); /* was tmp */
	index = (int)(res - str);
	index -= dif;
	
	return (index > 0? 1 : 0);
}

void string::keep_lines_start(char symbol)  /* bad name */
{
	int i, j = 0, index;
	char *p_index, *tmp = str;
	
	p_index = (char*)memchr(tmp, symbol, len);
	
	if(!p_index)
		return;
	index = p_index - tmp;
	for(i = index; i < len; i++)
	{
		tmp[j] = tmp[i];
		j++;
	}
	(*this).add_to_len(-(index));
	
	/*return (index > 0? p_index : 0);*/

}

string string::cut_line_start(char symbol) 
{
	string res;
	int index;

	index = (*this).find_symbol('\n');
	if (index == -1)
		return res;
	res.add_to_len(index + 1);
	memmove(res.str, str, index + 1);
	memmove(str, str + index, len - index - 1);
	(*this).add_to_len(-(index + 1));

	return res;
}

int string::find_symbol(char find) const
{
	for(int i = 0; i < len; i++)
		if (str[i] == find)
			return i;

	return -1;
}
