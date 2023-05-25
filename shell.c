#include "shell.h"

/**
 * main - runs a shell loop
 *
 * Return: Always 0 on success
 */

int main(void)
{
char *line = NULL;
size_t n = 0;
char *prompt = "$ ";
char **token;
pid_t wpid;
int status = 0;
bool pipe = false;
ssize_t numread;
while (1 & !pipe)
{
if (isatty(STDIN_FILENO) == 0)
pipe = true;
write(STDOUT_FILENO, prompt, 2);
numread =  getline(&line, &n, stdin);
if (numread == -1)
{
print("exiting shell...\n");
free(line);
return (-1);
}
token = splittoks(line);
wpid = fork();
if (wpid  == -1)
{
perror("fork");
exit(1);
}
else if (wpid == 0)
{
status = execmd(token);
}
if (waitpid(wpid, &status, 0) == -1)
{
perror("Error (wait)");
exit(EXIT_FAILURE);
}
freememory_pp(token);
}
free(line);
return (0);
}
