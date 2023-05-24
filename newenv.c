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

	if (cmd[1] == NULL)
	{
	write(STDOUT_FILENO, "./hsh: unsetenv: Invalid argument\n", 34);
	return (-1);
	}
	if (_unsetenv(cmd[1]) == -1)
	{
	getcwderr("unable to unset environment");
	return (-1);
	}
	return (0);
}
/**
 * current_dir - changes to the current directory
 * @cmd: unused
 *
 */
void current_dir(char **cmd)
{
	char pwd[BUFSIZE];
	char *cp_pwd;
	(void)cmd;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
	getcwderr("Failed to get current directory");
	return;
	}

	cp_pwd = _strdup(pwd);
	if (_setenv("OLDPWD", cp_pwd, 1) == -1)
	{
	getcwderr("Failed to set environment variable");
	free(cp_pwd);
	return;
	}
	free(cp_pwd);

	if (chdir(".") == -1)
	{
	getcwderr("Failed to change directory");
	return;
	}

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
	getcwderr("Failed to get current directory");
	return;
	}
	if (_setenv("PWD", pwd, 1) == -1)
	{
	getcwderr("Failed to set environment variable");
	return;
	}
}
/**
 * errunset - error message if unset cmd fails
 * @cmd: the command entered
 *
 * Return: returns the error message
 */
char *errunset(char *cmd)
{
	print("./hsh");
	print(": ");
	print(cmd);
	print(": ");
	print("unable to unset environmental variable");
	_putchar('\n');
	return ("1");
}
/**
 * getcwderr - get errors if the getcwd function returns NULL
 * @message: message to be printed
 *
 */
void getcwderr(char *message)
{
	size_t message_len = strlen(message);
	char newline = '\n';

	write(STDERR_FILENO, message, message_len);
	write(STDERR_FILENO, &newline, 1);
}
