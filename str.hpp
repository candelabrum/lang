#ifndef STR_CPP_H_SENTRY
#define STR_CPP_H_SENTRY

/* make more good name for method is_balanced_by */
class string
{
private:
	int len;
	int max_len;
	char *str;
public:
	void set(char *a_str, int a_len); /*was a_str = 0, a_len = 0*/
	string(const char *a_str = 0);
	void set(const char *a_str);
	string(const string &s);
	inline int get_len() const { return len; }
	/*inline void set_ch(char symbol, int index); */
	char* get_str() const;
	void add_to_len(int number);
	int find_symbol(char find) const; /* return index */
	char** MakeArgv();
	void keep_lines_start(char symbol);
	char have_sys_line(char symbol) const;
	char any_str_equal(const char **argv) const;
	string cut_line_start(char symbol);
	char& operator[](int index);
	int is_balanced_by(char open, char close) const;
	void print() const;
	~string();
	const string& operator=(const string& str);
	void print_f() const;
	bool is_equal(const char *a_str) const;
    bool is_equal(string &a_str) const;

};

#endif
