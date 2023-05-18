#include <stdio.h>
#include "shell.h"

int shell()
{
	int (*builtin_func)(char **, int, char *);
	char *line = NULL, *cmd_cpy = NULL;
	pid_t wpid;
	int status =0, wstatus;
	size_t n = 0;
	char **tokens = NULL;
	ssize_t lineread;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	print_prompt1();

	lineread = _getline(&line, &n, STDIN_FILENO);
	if (lineread == -1) {
        write(STDERR_FILENO, "Error reading input.\n", 21);
        return -1;
	}
	cmd_cpy = _strdup(line);

	tokens = token_cmd(cmd_cpy);
	if (!tokens || !tokens[0])
		continue;
	builtin_func = check_builtins(tokens);
	if (builtin_func)
	{
		status = builtin_func(tokens, status, tokens[0]);
		freememory_pp(tokens);
		free(cmd_cpy);
		continue;
	}
	else
	{
	wpid = fork();
	if (wpid == -1)
	{
	perror("fork failed:");
	exit (1);
	}else if (wpid == 0)
	{
	execute(line);
	exit (0);
	}
	if (waitpid(wpid, &wstatus, 0) == -1)
	{
		perror("Erro (wait)");
		exit(EXIT_FAILURE);	
	}
	}
	freememory_pp(tokens);
	free(cmd_cpy);
	free(line);
	}

	return (0);
}
