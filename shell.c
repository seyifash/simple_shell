#include <stdio.h>
#include "shell.h"
/**
* execute_builtin - executes the builtin command
* @builtin_func: function pointer to the builtin command
* @tokens: command tokens
* @status: current status
*
* Return: new status after executing the command
*/
int execute_builtin(
int (*builtin_func)(char **, int, char *),
char **tokens,
int status)
{
status = builtin_func(tokens, status, tokens[0]);
freememory_pp(tokens);
return (status);
}
/**
* execute_external - executes an external command
* @line: input line
*
* Return: 0 on success, -1 on failure
*/
int execute_external(char *line)
{
pid_t wpid;
int status = 0, wstatus;
wpid = fork();
if (wpid == -1)
{
perror("fork failed:");
exit(1);
}
else if (wpid == 0)
{
handle_cmd(line);
exit(0);
}
if (waitpid(wpid, &wstatus, 0) == -1)
{
perror("Error (wait)");
exit(EXIT_FAILURE);
}
return (status);
}
/**
* shell - runs a loop for the shell
*
* Return: 0 on success, -1 on failure
*/
int shell(void)
{
int (*builtin_func)(char **, int, char *);
char *line = NULL;
int status = 0;
size_t n = 0;
char **tokens = NULL;
ssize_t lineread;
bool pipe = false;

while (1 && !pipe)
{
if (isatty(STDIN_FILENO) == 0)
pipe = true;
print_prompt1();
lineread = _getline(&line, &n, STDIN_FILENO);
if (lineread == -1)
{
free(line);
return (-1);
}
tokens = token_cmd(line);
if (tokens == NULL || tokens[0] == NULL)
{
freememory_pp(tokens);
continue;
}

builtin_func = check_builtins(tokens);
if (builtin_func)
{
status = execute_builtin(builtin_func, tokens, status);
continue;
}
else
{
status = execute_external(line);
}
freememory_pp(tokens);
}
free(line);
return (0);
}

