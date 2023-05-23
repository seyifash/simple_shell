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

void print_prompt1(void);
void print_prompt2(void);

extern char **environ;


int shell();
char *printerror(char *cmd);
char *_getenv(const char *name);
char **token_cmd(char *line);
int execute(char *input);
void executeid(char *argv);
void handle_cmd(char *input);
void cmdsep_exec(char *input);
char *getlocation(char *command);
void execute_or(char *input);
void execute_and(char *input);
void execute_sep(char *input);
char *exspaces(char *input);

int _strncmp(char *s1, char *s2, int n);
size_t _strcspn(const char *str, const char *delim);
int _strspn(char *str, const char *acc);
char *_strncpy(char *dest, char *src, int n);
char *_strcat(char *dest, char *src);
char *_memset(char *s, char b, unsigned int n);
int _strlen(char *s);
char *_strchr(const char *str, int c);
char *_strcpy(char *dest, char *src);
char* _strstr(const char* haystack, const char* needle);
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
 * struct builtin_t structure for builrin commands
 * @cmd: the command's name
 * @c: the appropriate function to act on command
 */

typedef struct  builtin_t{

        char *cmd;
        int (*function_ptr)(char **, int, char *);
} builtin_t;

void Errormes(char *command);
void changeto_dir(char **dir);
int builtin_unset(char **cmd, int status, char *filename);
int  env_cmd(char **cmd, int status, char *filename);
int exit_cmd(char **cmd, int status, char *filename);
int built_setenv(char **cmd, int status, char *filename);
builtin_t is_builtin(char *cmd);
int (*check_builtins(char **))(char **, int, char *);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int cd_cmd(char **cmd, int status, char *filename);
void current_dir(char **cmd);
void change_givendir(char **cmd);
void change_prevdir(char **cmd);
void change_homedir(char **cmd);

unsigned int is_delim(char c, const char *delim);
char *_strtok(char *src, const char *delim);
ssize_t _getline(char **lineptr, size_t *n, int fd);
int find_exist( char *name, char *value, int overwrite);
char *new_var(char *name, char *value);
int _setenv(char *name, char *value, int overwrite);


#define TRUE 1
#define FALSE 0
#define BUFSIZE 1024
#define MAX_TOKENS 100

#endif
