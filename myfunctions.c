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
	_strcat(file_path, "\0");
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
	return (NULL);
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
	int argc = 0, i = 0;
	char **argv = NULL;

	cmd_cpy = _strdup(line);
	token = _strtok(line, delim);
	while (token != NULL)
	{
	argc++;
	token = _strtok(NULL, delim);
	}

	argv = malloc(sizeof(char *) * (argc + 1));
	if(!argv)
	{
	write(STDERR_FILENO, "Error: malloc failed\n", 21);
	exit(1);
	}

	token = _strtok(cmd_cpy, delim);

	while (token != NULL)
	{
	argv[i] = _strdup(token);
	i++;
	token = _strtok(NULL, delim);
	}
	argv[i] = NULL;

	free(cmd_cpy);

	return argv;
}
