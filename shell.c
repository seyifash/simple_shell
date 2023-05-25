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

execute(line);
}
free(line);
return (0);
}
