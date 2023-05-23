#include "shell.h"
/**
 * execute_sep - execute the commands with semicolon
 * @input: the command to be executed
 *
 */
void execute_sep(char *input)
{
	char *delim = ";";
	char *cmd_cpy = _strdup(input);
	char *cmd_token = _strtok(cmd_cpy, delim);

	while (cmd_token != NULL)
	{
	execute(cmd_token);
	cmd_token = _strtok(NULL, delim);
	}

	free(cmd_cpy);
}
/**
 * execute - executes commands entered
 * @cmd: the command
 *
 * Return: returns 0 on success
 */
int execute(char *cmd)
{
	char **md;
	char *command = NULL;
	char *actual_command = NULL;
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
	md = token_cmd(cmd);

	command = md[0];
	actual_command = getlocation(command);
	execve(actual_command, md, environ);
	perror("Execution failed");
	exit(1);
	}
	else if (pid > 0)
	{
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
	}
	else
	{
	perror("Fork failed");
	return (-1);
	}
}
/**
 * execute_and - executes commands with the AND logical operator
 * @input: the commmand entered
 *
 */
void execute_and(char *input)
{
	char *delim = "&&";
	char *cmdt = _strtok(input, delim);
	int prest = 0;

	while (cmdt != NULL)
	{
	if (prest == 0)
	{
	if (execute(cmdt) == 0)
	{
	prest = 0;
	}
	else
	{
	prest = 1;
	}
	}
	else
	{
	break;
	}

	cmdt = _strtok(NULL, delim);
	}

}
/**
 * execute_or - executes th cmd with the OR logical operators
 * @input: command entered
 *
 */
void execute_or(char *input)
{
	char *delim = "||\n";
	char *space;
	char *cmd_toks;
	char *pretok = NULL;
	int presame = 0;
	int ini_exec;

	cmd_toks = _strtok(input, delim);
	while (cmd_toks != NULL)
	{
	space = exspaces(cmd_toks);
	if (presame && pretok != NULL &&
	_strcmp(prevtok, space) == 0 && ini_exec == 0)
	{
	break;
	}
	else
	{
	ini_exec = execute(cmd_toks);
	}
	presame = 1;
	pretok = space;
	cmd_toks = _strtok(NULL, delim);
	}

}
/**
 * handle_cmd - handles and executes command
 * @input: the cmd entered
 *
 */
void handle_cmd(char *input)
{

	char *copy = _strdup(input);

	if (_strchr(input, ';') != NULL)
	{
	execute_sep(input);
	}
	else if (_strstr(input, "||") != NULL)
	{
	execute_or(copy);
	free(copy);
	}
	else
	{
	execute_and(input);
	}

}
