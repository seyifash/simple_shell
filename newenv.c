#include "shell.h"

/**
 * _unsetenv - unsets an enviromental variable
 * @name: the name of the environmental variable to be unset
 *
 * Return: returns 0 on succcess and -1 on failure
 */
int _unsetenv(char *name)
{

	int env_count = 0;
	int new_index = 0;
	char **new_env;
	int i;

	while (environ[env_count] != NULL)
	{
	env_count++;
	}
	new_env = (char **)malloc((env_count + 1) * sizeof(char *));
	if (new_env == NULL)
	{
	write(STDERR_FILENO, "Error: Failed to allocate memory\n", 32);
	return (-1);
	}
	new_index = 0;


	for (i = 0; i < env_count; i++)
	{
	if (_strncmp(environ[i], name, strlen(name)) != 0 ||
	environ[i][strlen(name)] != '=')
	{
	new_env[new_index++] = environ[i];
	}
	}

	new_env[new_index] = NULL;
	environ = new_env;

	return (0);
}

/**
 * builtin_unset - implements the unsetenv builtin command
 * @cmd: the given command
 * @status: unused
 * @filename: unused
 * Return: 0 on success and -1 on failure
 */
int builtin_unset(char **cmd, int status, char *filename)
{

	(void)status;
	(void)filename;

	if (_unsetenv(cmd[1]) == -1)
	{
	write(STDERR_FILENO, "Error: Failed to unset environment variable\n", 45);
	return (-1);
	}
	return (0);
}
