#ifndef STRING_H_SENTRY
#define STRING_H_SENTRY

#ifdef __cplusplus
extern "C"
{
#endif

int lenArgV(char **ArgV);
char str_equal(const char *str1, const char *str2);
char find_char_in(char *str, int len,  int search);
char** make_argv(char *str);
int str_to_int(char *str, int *number);
char* create_str(char *array, int end_index);
char is_number(char *str);
int str_len(char *str);
int len_of_number(int number);
void str_move(char *str1, char *str2, int len);
char* int_to_str(int number);
char any_str_equal(const char *str, const char **argV);
void free_argv(char **argv);

#ifdef __cplusplus
}
#endif

#endif
