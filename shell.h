#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>

void print_prompt1(void);
void print_prompt2(void);

extern char **environ;

int shell(void);
char *_getenv(const char *name);
char **token_cmd(char *line);
char *_strtok(char *src, const char *delim);
unsigned int is_delim(char c, const char *delim);
int execute(char **input, char *line);
void executeid(char *line);
char *getlocation(char *command);
char *exspaces(char *input);
void handlesig(int sigfunc);
ssize_t _getline(char **line, size_t *n, FILE *strm);

int _strncmp(char *s1, char *s2, int n);
size_t _strcspn(const char *str, const char *delim);
int _strspn(char *str, const char *acc);
char *_strncpy(char *dest, char *src, int n);
char *_strcat(char *dest, char *src);
char *_memset(char *s, char b, unsigned int n);
int _strlen(char *s);
char *_strchr(const char *str, int c);
char *_strcpy(char *dest, char *src);
char *_strstr(const char *haystack, const char *needle);
char *_strdup(char *str);
int _atoi(char *s);
int _isalpha(char c);
void _memcpy(void *dest, void *src, unsigned int n);

int _putchar(int c);
int print(char *str);


void free_space_p(char *ptr);
void freememory_pp(char **ptr);
int _strcmp(char *s1, char *s2);


/**
 * struct builtin_t - structure for builrin commands
 * @cmd: the command's name
 * @function_ptr: the appropriate function to act on command
 */

typedef struct  builtin_t
{

	char *cmd;
	int (*function_ptr)(char **, char *, char *, int);
} builtin_t;

int builtin_unset(char **cmd, char *line, char *filename, int status);
int  env_cmd(char **cmd, char *line, char *filename, int status);
int exit_cmd(char **cmd, char *line, char *filename, int status);
int built_setenv(char **cmd, char *line, char *filename, int status);
builtin_t cmpbuiltin(char *cmd);
int (*ifbuiltins(char **))(char **, char *, char *, int status);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int cd_cmd(char **cmd, char *line, char *filename);
int execmd(char **argv);
char **splittoks(char *line);
void updateline(char **line, size_t *n, char *buffer, size_t chread);

#define TRUE 1
#define FALSE 0
#define BUFSIZE 1024
#define MAX_TOKENS 100

#endif
