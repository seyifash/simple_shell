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
 * executeid - function that executes the given command
 * @cmd: the command to be executed
 *
 */
void executeid(char *cmd)
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
