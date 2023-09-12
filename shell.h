#ifndef SHELL_H
#define SHELL_H

/*
 * File: shell.h
 * Auth: Amal sayed
 *       JanviaveTharwat
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>


/* define and handling */
/* convert number handling */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* getline() handling */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* buffers handling*/
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command handling */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* history handling */
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/* get enviroment variable "user enviroment" */
extern char **environ;

/*structures*/

/**
 * struct listL - linked list
 * @num: field number
 * @str: str
 * @next: points to the next node
 */

typedef struct listL
{
	int num;
	char *str;
	struct listL *next;
} link_t;

/**
 * struct data_passed - allowing uniform prototype for function pointer struct
 * @arg: str  from getline containing arguements
 * @av: argument array of strs
 * @ac: the argument count
 * @path: str path for the current command
 * @readfd:  fd from which to read line input
 * @count_line: error counter
 * @error_exit: error for exit
 * @linecount_flag: count this line of input
 * @environ: custom modified copy of environ from env
 * @env: linked list local copy of environ
 * @env_changed: on if environ was changed
 * @history: history node
 * @count_history: history lines counter
 * @file_name: filename
 * @alias: alias node
 * @status: the return status of the last exec'd command
 * @buf_cmd: address of pointer to buf_cmd
 * @type_cmd: || "or"  &&  "and" ; "semicolme"
 */

typedef struct data_passed
{
	char *arg;
	char **av;
	char *path;
	int ac;
	unsigned int count_line;
	int error_exit;
	int linecount_flag;
	char *file_name;
	link_t *env;
	link_t *history;
	link_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **buf_cmd;
	int type_cmd;
	int readfd;
	int count_history;
} inputs_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtIn - contains a builtin str and function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtIn
{
	char *type;
	int (*func)(inputs_t *);
} builtIn_t;

/*prototype*/
/*shell_main */
int main(int ac, char **av);

/* alais*/
int alias(inputs_t *data);
int print_alias(link_t *node);
int set_alias(inputs_t *data, char *str);
int unset_alias(inputs_t *data, char *str);

/*build_in*/
int exiting(inputs_t *data);
int helper(inputs_t *data);
int archive(inputs_t *data);
int cur_cd(inputs_t *data);
void replace_hash(char *buf);
void error_msg(inputs_t *data, char *str);
void puts_str(char *str);
int putchar_stderr(char abc);
int decimal_10(int input, int fd);
int str_converter(char *str);
char *num_converter(int base, int flags, long int num);
int puts_str_fd(char *str, int fd);
int puts_fd(int fd, char abc);

/* data.c */
void set_data(char **av, inputs_t *data);
void clear_data(inputs_t *data);
void free_data(inputs_t *data, int free_all);

/*enviroment */
int domain(inputs_t *data);
int new_envioremt(inputs_t *data);
int remove_domain(inputs_t *data);

/*env*/
char *dom_val(inputs_t *data, const char *env_name);
int occupied_domain(inputs_t *data);
char **get_environ(inputs_t *data);

/* getline*/
ssize_t get_input(inputs_t *data, char **input, size_t *len);
int _getline(inputs_t *data, char **ptr, size_t *length);
ssize_t new_line(inputs_t *data);

/*  history_func*/
char *get_history(inputs_t *data);
int create_history(inputs_t *data);
int read_history(inputs_t *data);
int history_list(inputs_t *data, char *buf, int linecount);
int recall_history_list(inputs_t *data);

/*  linkedlists functions */
link_t *addnode_to_begining(link_t **, const char *, int);
link_t *addnode_to_end(link_t **head, const char *str, int index);
size_t write_list_strings(const link_t *);
int delete_node(link_t **, unsigned int);
void delete_list(link_t **);
size_t list_length(const link_t *);
char **str_list(link_t *);
size_t print_list(const link_t *);
link_t *begain_with_node(link_t *, char *, char);
ssize_t node_index(link_t *, link_t *);

/*looping*/
int shell_loop(inputs_t *data, char **av);
int buildIn_finder(inputs_t *data);

/*looping_helpers*/
int connected(inputs_t *data);
void cmd_finder(inputs_t *data);
void cmd_fork(inputs_t *data);

/*  memory.c */
int free_ptr(void **p);

/* parseing */
int check_cmd(inputs_t *, char *);
char *duplicate_chars(char *, int, int);
char *get_path(inputs_t *, char *, char *);

/* real_loc*/
char *_memset(char *, char, unsigned int);
void free_str(char **);
void *redistribute(void *, unsigned int, unsigned int);

/*replace build in */
int replace_token_var(inputs_t *data);
int replace_str(char **o, char *n);
int replace_alias(inputs_t *data);

/*set_unset_enviroment.c */
int _setenv(inputs_t *data, char *ev, char *e_val);
int _unsetenv(inputs_t *data, char *ev);

/* str/num conv */
int check_abc(int abc);
int check_delim(char chars, char *delim);
int _atoi(char *converter);

/*stings maniuplation*/
int _strlen(char *);
int _strcmp(char *, char *);
char *begain_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/*symbols*/
int chain_tester(inputs_t *data, char *buf, size_t *ptr);
void check_chain(inputs_t *data, char *buf, size_t *ptr,
		 size_t index, size_t lg);

/* token */
char **tok_str(char *s, char *b);
char **tok_str_b(char *s, char b);


#endif
