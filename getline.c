#include "shell.h"

/**
 * _getline - reads input from stdin
 * @line: the buffer that stores the characters read from stdin
 * @n: the number of characters to be read from stdin
 * @fd: the file which getline reads from
 * Return: return the total number of characters read
 */

ssize_t _getline(char **line, size_t *n, int fd)
{
	static char buffer[BUFSIZE];
	ssize_t charsread = 0;
	ssize_t totalread = 0;
	ssize_t rd;

	if (line == NULL || (int)*n >= 0)
	{
	*n = BUFSIZE;
	*line = malloc(*n);
	if (*line == NULL)
	{
	return (-1);
	}
	}
	
	while (1)
	{
	rd = read(fd, buffer, BUFSIZE);
	if (rd == -1)
	return (-1);
	if (rd == 0)
	break;
	charsread += rd;
	totalread += rd;
	if ((size_t)charsread >= *n - 1)
	{
	do {
	*n *= 2;
	} while ((size_t)charsread >= *n - 1);
	*line = _realloc(*line, *n / 2, *n);
	if (*line == NULL)
	{
	return (-1);
	}
	}
	_strncpy(*line + totalread - rd, buffer, rd);
	if (buffer[rd - 1] == '\n')
	break;
	}
	(*line)[totalread] = '\0';
	return (totalread);
}
/**
 * execute - function that executes the given command
 * @argv: the command to be executed
 *
 */
void execute(char **cmd)
{
	pid_t pid;
	int status;
	char *command = NULL, *actual_command = NULL;

	pid = fork();

	if (pid == -1)
	{
	perror("Error");
	exit (EXIT_FAILURE);
	}
	if (pid == 0)
	{

	if (cmd)
	{
	command = cmd[0];
	actual_command = getlocation(command);
	if (execve(actual_command, cmd, environ) == -1)
	{
	perror("Error");
	exit(EXIT_FAILURE);
	}
	}
	exit(EXIT_SUCCESS);
	}
	else
	{
	if (wait(&status) == -1)
	{
	perror("wait failed");
	exit(EXIT_FAILURE);
	}

	if (WIFEXITED(status))
	exit(WEXITSTATUS(status));
	}
}
/**
 * _memcpy - copies info
 * @newptr: destination
 * @ptr: source
 * @n: size
 * Return: nth - returns nth
 */
void _memcpy(void *dest, void *src, unsigned int n)
{
	char *char_src = (char *)src;
	char *char_dest = (char *)dest;
	unsigned int i;

	for (i = 0; i < n; i++)
	char_dest[i] = char_src[i];
}
