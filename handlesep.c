#include "shell.h"
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
	int status;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
	md = splittoks(cmd);
	command = md[0];
	execve(command, md, environ);
	perror("Error");
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

	freememory_pp(md);
}
/**
 * execmd - executes the command
 * @argv: the command to execute
 */
int execmd(char **argv)
{
	char *command = NULL;

	if (argv)
	{
	command = argv[0];
	if (execve(command, argv, NULL) == -1)
	{
	perror("./shell");
	freememory_pp(argv);
	exit(EXIT_FAILURE);
	}
	}
	freememory_pp(argv);
	return (0);
}
/**
 * splittoks - split commands into individuat strings
 * @line: the command to split
 *
 * Return: returns the tokenized string
 */
char **splittoks(char *line)
{
	char *token;
	char **toks;
	int numtoks = 0;
	char *delim = " \t\n\r\a";
	int i;
	char *cmd_cpy;

	cmd_cpy = _strdup(line);
	token = strtok(cmd_cpy, delim);
	while (token != NULL)
	{
	numtoks++;
	token = strtok(NULL, delim);
	}
	toks = malloc(sizeof(char *) * (numtoks + 1));
	token = strtok(line, delim);
	for (i = 0; token != NULL; i++)
	{
	toks[i] = malloc(sizeof(char) * (_strlen(token) + 1));
	strcpy(toks[i], token);
	token = strtok(NULL, delim);
	}
	toks[i] = NULL;
	free(cmd_cpy);
	return (toks);
}
