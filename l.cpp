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


