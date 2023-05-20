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
	ssize_t charsread = 0, totalread = 0, rd = 0;
	size_t new_size = 0;
	char  *new_line = NULL;

	if (line == NULL || (int)*n >= 0)
	{
	*n = BUFSIZE;
	*line = malloc(*n);
	if (*line == NULL)
	return (-1);
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
	new_size = *n * 2;
	new_line = _realloc(*line, *n, new_size);
	if (new_line == NULL)
	{
	free(*line);
	*line = NULL;
	return (-1);
	}
	*line = new_line;
	*n = new_size;
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
 * @cmd: the command to be executed
 *
 */
void execute(char *cmd)
{
	char **argv;
	char *command = NULL, *actual_command = NULL;

	argv = token_cmd(cmd);
	command = argv[0];
	actual_command = getlocation(command);
	execve(actual_command, argv, environ);
	freememory_pp(argv);
	free(actual_command);
	free(cmd);
}
/**
 * _memcpy - copies info
 * @dest: destination
 * @src: source
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
/**
 * is_accessible - checks if a file is accessible
 * @actual_command: the file to be checked
 *
 * Return: 0 0n success and 1 0n failure
 */
int is_accessible(char *actual_command)
{
	if (access(actual_command, F_OK) == 0)
	{
	if (access(actual_command, R_OK | X_OK) == 0)
	{
	return (1);
	}
	else
	{
	return (0);
	}
	}
	return (0);
}


