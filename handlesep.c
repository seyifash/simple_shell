#include "shell.h"
/**
 * execute_sep - execute the commands with semicolon
 * @input: the command to be executed
 *
 */
void execute_sep(char *input)
{
	char* delim = ";";
	char* cmd_cpy = _strdup(input);
	char* cmd_token = _strtok(cmd_cpy, delim);

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
	char **argv;
	char *command = NULL;
	char *actual_command = NULL;
	int status;
	
	pid_t pid = fork();
	if (pid == 0)
	{
	argv = token_cmd(cmd);

	command = argv[0];
	actual_command = getlocation(command);
	execve(actual_command, argv, environ);
	perror("Execution failed");
	exit(1);
	} 
	else if (pid > 0)
	{
	waitpid(pid, &status, 0);
	return WEXITSTATUS(status);
	} 
	else 
	{
	perror("Fork failed");
	return -1;
	}
}
/**
 * execute_and - executes commands with the AND logical operator
 * @input: the commmand entered
 *
 */
void execute_and(char *input)
{
	char* delim = "&&";
	char* cmd_cpy = _strdup(input);
	char* cmd_token = _strtok(input, delim);

	int prev_status = 0;

	while (cmd_token != NULL)
	{
	if (prev_status == 0)
	{
	if (execute(cmd_token) == 0) {
	prev_status = 0;
	}
	else
	{
	prev_status = 1;
	}
	}
	else
	{
	break;
	}

	cmd_token = _strtok(NULL, delim);
	}

	free(cmd_cpy);
}
/**
 * execute_or - executes th cmd with the OR logical operators
 * @input: command entered
 *
 */
void execute_or(char *input)
{
	char* delim = "||";
	char* cmd_cpy = _strdup(input);
	char* cmd_token = _strtok(cmd_cpy, delim);

	while (cmd_token != NULL)
	{
	execute(cmd_token);
	cmd_token = _strtok(NULL, delim);
	}

	free(cmd_cpy);
}
/**
 * handle_cmd - handles and executes command
 * @input: the cmd entered
 *
 */
void handle_cmd(char *input)
{
	if (_strchr(input, ';') != NULL) 
	{
	execute_sep(input);
	}
	else if (_strstr(input, "&&") != NULL) 
	{
	execute_and(input);
	}
	else if (_strstr(input, "||") != NULL) 
	{
	if (checkcmdsame(input)) 
	{
	execute(input);
	} 
	else 
	{
	execute_or(input);
	}	
	}
	else 
	{
	execute(input);
	}
}
/**
 * checkcmdsame - check if the commands are the same
 * @input: the cmd entered
 *
 * Return: returns  1 if cmd is same
 */
int checkcmdsame(char *input) 
{
	char *delim = "||";
	char *cmd_cpy = _strdup(input);
	char *cmd_token;
	char *first_command = NULL;
	int same_commands = 1;

	cmd_token = _strtok(cmd_cpy, delim);
	first_command = _strdup(cmd_token);
	
	while (cmd_token != NULL) {
	if (_strcmp(cmd_token, first_command) != 0) {
	same_commands = 0;
	break;
	}
	cmd_token = _strtok(NULL, delim);
	}

	free(cmd_cpy);
	free(first_command);
	return same_commands;
}
