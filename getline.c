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

	if (line == NULL || n == NULL)
	return (-1);
	*n = BUFSIZE;
	*line = buffer;

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
 * printenv - prints environ variables
 *
 */
void printenv(void)
{
char **env = environ;
size_t len;
char *curr;
while (*env != NULL)
{
len = 0;
curr = *env;
while (*curr != '\0')
{
len++;
curr++;
}
write(STDOUT_FILENO, *env, len);
write(STDOUT_FILENO, "\n", 1);

env++;
}
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
 * exspaces - a function that removes spaces from the string
 * @input: the string toremove spaces from
 *
 * Return: returs strings without space
 */
char *exspaces(char *input)
{
	char *rmsp = NULL;
	int i;
	int j;
	int len = _strlen(input);

	rmsp = malloc(len + 1);
	if (rmsp == NULL)
	{
	perror("malloc");
	return (NULL);
	}
	j = 0;
	for (i = 0; i < len; i++)
	{
	if (input[i] != ' ')
	{
	rmsp[j] = input[i];
	j++;
	}
	}
	rmsp[j] = '\0';
	return (rmsp);
}
/**
 * printerror - prints an error if the execute function fails
 * @cmd: the command that failed
 *
 * Return: returns the ascii 1 if it fails to print
 */
char *printerror(char *cmd)
{
	print("./hsh");
	print(": ");
	print(cmd);
	print(": ");
	print("No such file or directory");
	_putchar('\n');
	return ("1");
}
