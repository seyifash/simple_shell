#include "shell.h"
/**
* is_builtin - checks if the command given is a built-in function
* @cmd: command entered
* Return: the position of cmd in the builtin array
*/
builtin_t is_builtin(char *cmd)
{
	int i;

	builtin_t builtincommands[] = {
	{"exit", exit_cmd},
	{"env", env_cmd},
	{"cd", cd_cmd},
	{"setenv", built_setenv},
	{"unsetenv", builtin_unset},
	{NULL, NULL}
	};

	for (i = 0; builtincommands[i].cmd != NULL; i++)
	if (_strcmp(builtincommands[i].cmd, cmd) == 0)
	return (builtincommands[i]);
	return (builtincommands[i]);
}
/**
* check_builtins - if command is a builtin command
* @cmd: an array of command and its argument
*
* Return: the appropriate function to be executed, else NULL
*/
int (*check_builtins(char **cmd))(char **, int, char *)
{
builtin_t func;
func = is_builtin(cmd[0]);
if (func.cmd)
return (func.function_ptr);
return (NULL);
}
/**
* env_cmd - builtin implementation of env command
* @cmd: unused
* @status: the status code
* @filename: name of file
*
* Return: Always 0
*/
int env_cmd(char **cmd, int status, char *filename)
{
int i;
(void)cmd;
(void)status;
(void)filename;
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
* @status: the status code
* @filename: name of file
*
* Return: exit with the status code given or previous execution
* status code
*/
int exit_cmd(char **cmd, int status, char *filename)
{
int i;
status = 0;
if (!cmd[1])
{
freememory_pp(cmd);
exit(status);
}
i = 0;
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
exit(status);
}
/**
* built_setenv - sets an environmental variable
* @cmd: the command entered
* @status: unused
* @filename: unused
* Return: returns 0 on success
*/
int built_setenv(char **cmd, int status, char *filename)
{

(void)status;
(void)filename;
if (cmd[1] == NULL || cmd[2] == NULL)
{
printenv();
}
else if (_setenv(cmd[1], cmd[2], 1) == -1)
{
getcwderr("Failed to set environmental variable");
return (-1);
}

return (0);
}
