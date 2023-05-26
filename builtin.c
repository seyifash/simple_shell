#include "shell.h"
/**
* cmpbuiltin - checks if the command given is a built in function
* @cmd: command entered
* Return: the position of cmd in the builtin array
*/
builtin_t cmpbuiltin(char *cmd)
{
int i;
builtin_t builtincommands[] = {
{"exit", exit_cmd},
{"env", env_cmd},
{NULL, NULL}
};
for (i = 0; builtincommands[i].cmd != NULL; i++)
if (_strcmp(builtincommands[i].cmd, cmd) == 0)
return (builtincommands[i]);
return (builtincommands[i]);
}
/**
* ifbuiltins - if command is a builtin command
* @cmd: an array of command and its argument
*
* Return: the appropriate function to be executed, else NULL
*/
int (*ifbuiltins(char **cmd))(char **, char *, char *, int)
{
builtin_t func = cmpbuiltin(cmd[0]);
if (func.cmd)
return (func.function_ptr);
return (NULL);
}
/**
* env_cmd - builtin implementation of env command
* @cmd: unused
* @line: the initial input before tokenization
* @filename: name of file
* @status: unised
*
* Return: Always 0
*/
int env_cmd(char **cmd, char *line, char *filename, int status)
{
int i;
(void)cmd;
(void)line;
(void) filename;
(void)status;
for (i = 0; environ[i]; i++)
{
print(environ[i]);
_putchar('\n');
}
return (0);
}
/**
* exit_cmd - builtin implementation of the exit command
* @cmd: an array of given commands and its argument
* @line: the initial input before tokenization
* @filename: name of file
* @status: the status code
* Return: exit with the status code given or previous execution
* status code
*/
int exit_cmd(char **cmd, char *line, char *filename, int status)
{
	int i = 0;

	if (!cmd[1])
	{
	freememory_pp(cmd);
	free(line);
	exit(status);
	}
	while (cmd[1][i])
	{
	if (_isalpha(cmd[1][i]) && cmd[1][i] != '-')
	{
	print(filename);
	print(": ");
	print(cmd[0]);
	print(": ");
	print("Illegal number: ");
	print(cmd[1]);
	_putchar('\n');
	return (1);
	}
	i++;
	}
	status = _atoi(cmd[1]);
	freememory_pp(cmd);
	free(line);
	exit(status);
	}
