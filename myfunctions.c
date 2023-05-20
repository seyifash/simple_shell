#include "shell.h"

/**
 * _getenv - get the value of an environmental variable
 * @name: the variable name
 *
 * Return: the value of name
 */
char *_getenv(const char *name)
{
	int i = 0, j = 0;

	while (environ[i])
	{
	while (environ[i][j] && *name)
	{
	if (environ[i][j] != *name || (environ[i][j] == '='))
	break;
	j++, name++;
	}
	if (environ[i][j] == '=' && !*name)
	return ((environ[i] + ++j));
	i++;
	}
	return (0);
}

/**
 * getlocation - gets the path of a command
 * @command: the command whose path is to be checked
 *
 * Return: returns the cmd path on success, NULL on failure
 */
char *getlocation(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path = _getenv("PATH");
	if (path)
	{
	path_copy = _strdup(path);
	command_length = _strlen(command);
	path_token = _strtok(path_copy, ":");
	while (path_token != NULL)
	{
	directory_length = _strlen(path_token);
	file_path = malloc(command_length + directory_length + 2);
	_strcpy(file_path, path_token);
	_strcat(file_path, "/");
	_strcat(file_path, command);
	if (stat(file_path, &buffer) == 0)
	{
	free(path_copy);
	return (file_path);
	}
	else
	{
	free(file_path);
	path_token = _strtok(NULL, ":");
	}
	}
	free(path_copy);
	if (stat(command, &buffer) == 0)
	{
	return (command);
	}
	}

	return (NULL);
}
/**
 * token_cmd - tokenizes the string
 * @line: the string to be tokenize
 *
 * Return: returns the tokenized string
 */

char **token_cmd(char *line)
{

	char *cmd_cpy = NULL;
	char *token = NULL;
	char *delim = " \n";
	int args = 0, i;
	char **cmd_toks = NULL;

	cmd_cpy = _strdup(line);
	token = _strtok(line, delim);
	while (token != NULL)
	{
	args++;
	token = _strtok(NULL, delim);
	}

	cmd_toks = malloc(sizeof(char *) * (args + 1));
	if(!cmd_toks)
	{
	write(STDERR_FILENO, "Error: malloc failed\n", 21);
	exit(1);
	}

	token = _strtok(cmd_cpy, delim);

	for(i = 0; token != NULL; i++)
	{
	cmd_toks[i] = malloc(sizeof(char) * _strlen(token));
	_strcpy(cmd_toks[i], token);
	token = _strtok(NULL, delim);
	}
	cmd_toks[i] = NULL;

	free(cmd_cpy);

	return cmd_toks;
}
/**
 * cmdsep_exec - handles commands with seperators and executes them
 * @input: the commands to be executed
 *
 */
void cmdsep_exec(char *input)
{
	char* delim = ";||&&";
	char* token = strtok(input, delim);
	pid_t pid;
	int status;

	while (token != NULL) {
	pid = fork();
	if (pid == 0)
	{
	execute(token);
	}
	else if (pid > 0)
	{
	waitpid(pid, &status, 0);
        }
	else
	{
	perror("Fork failed");
	exit(1);
	}

	token = strtok(NULL, delim);
	}

}
/**
 * handle_exec_cmd - checkes if a command is seperated by seperators
 * @input: the commands entered
 *
 */
void handle_exec_cmd(char *input)
{
	if (strstr(input, ";") != NULL)
	{
	cmdsep_exec(input);
	}
	else if (strstr(input, "||") != NULL)
	{
		cmdsep_exec(input);
	}
	else if (strstr(input, "&&") != NULL)
	{
		cmdsep_exec(input);
	}
	else
	{
        execute(input);
	}
}