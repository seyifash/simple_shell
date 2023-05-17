#include "shell.h"

/**
 * print_prompt1 - prints the prompt for user
 *
 */

void print_prompt1(void)
{
	write(STDERR_FILENO, "$ ", 2);
}
/**
 * is_delim - checks if the character in the string is a delimiter
 * @c: the characcter to be checked
 * @delim: the delimiting character to be checaked
 *
 * Return: returns 1 if the delimiter is found, else 0;
 */
unsigned int is_delim(char c, const char *delim)
{

	while (*delim != '\0')
	{
	if (c == *delim)
	return (1);
	delim++;
	}
	return (0);
}
/**
 * _strtok - tokenizes a string
 * @src: the string to be tokenized
 * @delim: the delimiter
 *
 * Return: returns the tokenized string
 */
char *_strtok(char *src, const char *delim)
{
	static char *backup;
	char *token = NULL;
	char *end = NULL;

	if (src == NULL)
	{
	src = backup;
	}
	if (src == NULL)
	{
	return (NULL);
	}
	src += _strspn(src, delim);
	if (*src == '\0')
	{
	backup = src;
	return (NULL);
	}
	end = src + _strcspn(src, delim);
	if (*end == '\0')
	{
	backup = end;
	}
	else
	{
	*end = '\0';
	backup = end + 1;
	}
	token = src;
	return (token);
}

/**
 * free_space_p - free a pointer
 *
 * @ptr: pointer to free
 */
void free_space_p(char *ptr)
{
	if (ptr != NULL)
	{
	free(ptr);
	ptr = NULL;
	}
	ptr = NULL;
}


/**
 * freememory_pp - frees a double pointer
 *
 * @ptr: Double pointer to free
 */

void freememory_pp(char **ptr)
{
	char **tmp;

	for (tmp = ptr; *tmp != NULL; tmp++)
	free_space_p(*tmp);
	free(ptr);
}
