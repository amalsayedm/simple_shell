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
 * @s: str
 * @next: points to the next node
 */

typedef struct listL
{
	int num;
	char *s;
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
	int ac;
	char *path;
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
	char **buf_cmd; /* pointer to cmd ; chain buffer, for memory mangement */
	int type_cmd;
	int readfd;
	int count_history;
} inputs_t;

#define data_INIT \
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
/*loop_shell */
int shell_loop(inputs_t *, char **);
int buildIn_finder(inputs_t_t *);
void cmd_finder(inputs_t *);
void cmd_fork(inputs_t *);

/* parser.c */
int cmd(inputs_t *, char *);
char *duplicated_char(char *, int, int);
char *path_finder(inputs_t *, char *, char *);

/* errors.c */
void puts_str(char *);
int putchar_stderr(char);
int puts_fd(char c, int fd);
int puts_str_fd(char *str, int fd);

/*  erors1.c */
int aoit2(char *);
void error_msg(inputs_t *, char *);
int decimal_10(int, int);
char *num_converter(long int, int, int);
void replace_hash(char *);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *begain_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer.c */
char **tok_str(char *, char *);
char **tok_str_b(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void free_str(char **);
void *redistribute(void *, unsigned int, unsigned int);

/*  memory.c */
int free_ptr(void **);

/* atoi.c */
int connected(inputs_t *);
int check_delim(char, char *);
int check_abc(int);
int _atoi(char *);



/* buildin .c*/
int exiting(inputs_t *);
int _mycd(inputs_t *);
int helper(inputs_t *);

/*  builtin1.c */
int archive(inputs_t *);
int alias(inputs_t *);

/* getline.c */
ssize_t get_input(inputs_t *);
int _getline(inputs_t *, char **, size_t *);
void copy_blocker(int);

/*  getinfo.c */
void clear_data(inputs_t *);
void set_data(inputs_t *, char **);
void free_data(inputs_t *, int);

/*  environ.c */
char *dom_val(inputs_t *, const char *);
int domain(inputs_t *);
int new_envioremt(inputs_t *);
int remove_domain(inputs_t *);
int occupied_domain(inputs_t *);

/*  getenv.c */
char **get_environ(inputs_t *);
int _unsetenv(inputs_t *, char *);
int _setenv(inputs_t *, char *, char *);

/*  history.c */
char *get_history(inputs_t *data);
int create_history(inputs_t *data);
int read_history(inputs_t *data);
int history_list(inputs_t *data, char *buf, int linecount);
int recall_history_list(inputs_t *data);

/*  lists.c */
link_t *add_to_begining_node(link_t **, const char *, int);
link_t *add_to_end_node(link_t **, const char *, int);
size_t list_str(const link_t *);
int delete_index_node(link_t **, unsigned int);
void list_free(link_t **);

/*  lists1.c */
size_t list_length(const link_t *);
char **str_list(link_t *);
size_t print_list(const link_t *);
link_t *begain_with_node(link_t *, char *, char);
ssize_t node_index(link_t *, link_t *);

/*  vars.c */
int chain_tester(inputs_t *, char *, size_t *);
void check_chain(inputs_t *, char *, size_t *, size_t, size_t);
int replace_alias(inputs_t *);
int replace_token_var(inputs_t *);
int replace_str(char **, char *);

#endif