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
	cmd_toks[i] = malloc(sizeof(char) * (_strlen(token) + 1));
	_strcpy(cmd_toks[i], token);
	token = _strtok(NULL, delim);
	}
	cmd_toks[i] = NULL;

	free(cmd_cpy);

	return cmd_toks;
}

/**
 * _strchr - function checks for the first occurence of a character in a string
 * @str: the string to be searched
 * @c: the string to search
 * Return: returnsremaining portion of string if found else NULL
 */

char *_strchr(const char *str, int  c)
{

	while (*str != '\0')
	{
	if (*str == c)
	return ((char *)(str));
	str++;
	}
	return (NULL);
}
/**
 * _strstr - searches for the first occurence of a string in anothr string
 * @haystack: the string in which the search occurs
 * @needle: the string to be searched for
 * Return: returns the substring if the needles is found else null
 */
char* _strstr(const char* haystack, const char* needle)
{
	int i, j;

	for (i = 0; haystack[i] != '\0'; i++)
	{
	j = 0;
	while (needle[j] != '\0' && haystack[i + j] == needle[j])
	{
	j++;
	}
	if (needle[j] == '\0')
	{
	return (char*)&haystack[i];
	}
	}

	return NULL;
}
