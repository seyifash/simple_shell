#include "shell.h"

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
