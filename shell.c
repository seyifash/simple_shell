#include "shell.h"

/**
 * main - runs a shell loop
 * @ac: unused
 * @argv: the filename
 *
 * Return: Always 0 on success
 */

int main(int ac __attribute__((unused)), char *argv[])
{
int (*builtin_func)(char **, char *, char *, int);
char *line = NULL;
size_t n = 0;
char **token = NULL;
char *prompt = "$ ";
ssize_t numread;
int status = 0;
signal(SIGINT, handlesig);
while (1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, prompt, 2);
numread =  getline(&line, &n, stdin);
if (numread == -1)
{
free(line);
if (isatty(STDIN_FILENO))
print("\n");
exit(0);
}
if (*line == '\n' || *line == '\0')
continue;
token = splittoks(line);
if (!token || !token[0])
{
freememory_pp(token);
continue;
}
builtin_func = ifbuiltins(token);
if (builtin_func)
{
builtin_func(token, line, argv[0], status);
freememory_pp(token);
continue;
}
status = execute(token, line);
freememory_pp(token);
}
free(line);
return (0);
}
