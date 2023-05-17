#include <stdio.h>
#include "shell.h"

int main(int argc __attribute__((unused)), char *argv[])
{
	int (*builtin_func)(char **, int, char *);
	char *line = NULL;
	pid_t wpid;
	int wstatus;
	size_t n = 0;
	char **tokens = NULL;
	int status = 0;
	ssize_t lineread;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	print_prompt1();

	lineread = _getline(&line, &n, STDIN_FILENO);
	if (lineread == -1) {
        printf("Error reading input.\n");
        return -1;
	}
	if (*line == '\n' || *line == '\0')
	continue;

	tokens = token_cmd(line);
	if (!tokens || !tokens[0])
		continue;
	builtin_func = check_builtins(tokens);
	if (builtin_func)
	{
		status = builtin_func(tokens, status, argv[0]);
		freememory_pp(tokens);
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
	execute(tokens);	
	freememory_pp(tokens);
	exit (0);
	}
	if (waitpid(wpid, &wstatus, 0) == -1)
	{
		perror("Erro (wait)");
		exit(EXIT_FAILURE);
		
	}
	}
	}


    free(line);
    return 0;
}
