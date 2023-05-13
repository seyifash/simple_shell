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
	size_t rd;

	if (line == NULL || *n >= 0)
	{
	*line = malloc(BUFSIZE);
	if (line == NULL)
	{
	return (-1);
	}
	}
	(*line)[0] = '\0';
	while (1)
	{
	rd = read(fd, buffer, BUFSIZE);
	if (rd == -1)
	return (-1);
	if (rd == 0)
	break;
	charsread += rd;
	totalread += rd;
	if (charsread >= *n - 1)
	{
	do {
	*n *= 2;
	} while (charsread >= *n - 1);
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
