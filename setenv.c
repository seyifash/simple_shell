#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char **environ

int find_exist(const char *name, const char *value);
char **token_cmd(char *line);
char *new_var(const char *name, const char *value);
int _setenv(char **args, int num_args, char *filename);
/**
 * new_var - creates a nw environmental variable
 * @name: name of the environmental varaiable to set
 * @value: value to which the environmental variable is to be set to
 * Return: returns the new environmental varaiable
 */

char *new_var(const char *name, const char *value)
{
	size_t len_name = strlen(name);
	size_t len_value = strlen(value);
	size_t len_total = 0;
	char *new_env;
	size_t i;
	size_t j;

	len_total = len_name + len_value + 2;
	new_env = (char *) malloc(len_total * sizeof(char));

	if (new_env == NULL)
	{
	return (NULL);
	}
	for (i = 0; i < len_name; i++)
	{
	new_env[i] = name[i];
	}
	new_env[i++] = '=';
	for (j = 0; j < len_value; j++, i++)
	{
	new_env[i] = value[j];
	}
	new_env[i] = '\0';

	return (new_env);
}
/**
 * _setenv - sets a new environmental variable
 * @args: the given commands
 * @num_args: number of arguments entered
 * @filename: second argument passed to the command
 * Return: returns 0 on success
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char *env = NULL;
	int i;
	int envc;
	char **new_environ;
	const char *variable;
	const char *value;


	if (num_args != 3)
	{
	printf("usage: setenv <variable> <value>\n");
	return (-1);
	}
	variable = args[1];
	value = args[2];


	if (find_exist(name, value) == -1)
	{
	envc = 0;
	while (environ[envc] != NULL)
	{
	envc++;
	}
	new_environ = malloc((envc + 2) * sizeof(char *));
	if (new_environ == NULL)
	{
	return (-1);
	}
	for (i = 0; i < envc; i++)
	{
	new_environ[i] = environ[i];
	}

	new_environ[envc++] = new_var(name, value);
	new_environ[envc] = NULL;
	environ = new_environ;

	free(new_environ[envc]);
	return (0);
	}
	free(env);
	return (0);

}

/**
 * find_exist - finds the variable if at already exist
 * @name: variable name
 * @value: the value to be set to the existing variable
 * Return: returns 0 on success
 */
int find_exist(const char *name, const char *value)
{
	char *env;
	size_t len_name = strlen(name);
	char **dupenv = environ;

	while (*dupenv != NULL)
	{
	if (strncmp(name, *dupenv, len_name) == 0 && (*dupenv)[len_name] == '=')
	{
	env = new_var(name, value);
	*dupenv = env;
	return (0);
	}
	dupenv++;
	}
	return (-1);
}

/**
 * token_cmd - tokenizes the string
 * @line: string to be tokenized
 *
 * Return: returns a the tokenized string
 */
char **token_cmd(char *line)
{

	char *cmd_cpy = NULL;
	char *token = NULL;
	char *delim = " \n";
	int argc = 0, i = 0;
	char **argv = NULL;

	cmd_cpy = strdup(line);
	token = strtok(line, delim);
	while (token != NULL)
	{
	argc++;
	token = strtok(NULL, delim);
	}

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
	{
	printf("Error: malloc failed\n");
	exit(1);
	}

	token = strtok(cmd_cpy, delim);

	while (token != NULL)
	{
	argv[i] = strdup(token);
	i++;
	token = strtok(NULL, delim);
	}
	argv[i] = NULL;

	free(cmd_cpy);

	return (argv);
}

/**
 * main - calls all other function
 *
 * Returns: Always 0 on success
 */

int main(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t line_length = 0;
	int num_args = 0;
	int env_index;
	char **args;

	while (1)
	{
	printf("> ");
	line_length = getline(&line, &bufsize, stdin);
	if (line_length == -1)
	{
	return (-1);
	}

	args = token_cmd(line);
	if (args == NULL)
	{
	perror("failed to tokenize the line");
	return (-1);
	}
	while (args[num_args] != NULL)
	{
	num_args++;
	}

	if (num_args > 0 && strcmp(args[0], "setenv") == 0)
	{
	_setenv(args, num_args, args[1]);
	}

	env_index = 0;
	while (environ[env_index] != NULL)
	{
	printf("%s\n", environ[env_index]);
	env_index++;
	}

	free(line);
	free(args);
	}
	return (0);
}
