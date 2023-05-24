#include "shell.h"

/**
* _strcmp - compares two strings
* @s1: first string
* @s2: second string
*
* Return: 0 if equal, -1 if s1 < s2, else +ve
*/
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i]; i++)
	if (s1[i] != s2[i])
	return (s1[i] - s2[i]);
	return (0);
}

/**
 * _strncmp - compares the first n characters of s1 and s2
 * @s1: string to compare
 * @s2: string to compare
 * @n: number of bytes to compare
 * Return: returns 0 if they match else -1 or 1
 */

int _strncmp(char *s1, char *s2, int n)
{
	int i;
	int a1, a2;

	for (i = 0; i < n; i++)
	{
	if (s1[i] == s2[i])
	{
	if (i == (n - 1))
	return (0);
	}

	a1 = (int) s1[i];
	a2 = (int) s2[i];
	if (a1 > a2)
		return (1);
	if (a2 > a1)
	return (-1);
	}

	return (0);
}
/**
 * _strspn - gets the length
 * @str: initial segment
 * @acc: accepted bytes
 * Return: num of accepted bytes - return bytes
 */
int _strspn(char *str, const char *acc)
{
	int i, j, found;

	for (i = 0; *(str + i) != '\0'; i++)
	{
	found = 0;
	for (j = 0; *(acc + j) != '\0'; j++)
	{
	if (*(str + i) == *(acc + j))
	{
	found = 1;
	break;
	}
	}
	if (found == 0)
	break;
	}
	return (i);
}
/**
 * _strcspn - a function that searches a string for a set of bytes
 * @str:the string to be searched
 * @delim: the string to be searche for in str
 * Return: returns the length of the initial segment of str not in delim
 */
size_t _strcspn(const char *str, const char *delim)
{
	const char *s;
	const char *d;

	for (s = str; *s != '\0'; s++)
	{
	for (d = delim; *d != '\0'; d++)
	{
	if (*s == *d)
	{
	return ((size_t)(s - str));
	}
	}
	}

	return ((size_t)(s - str));
}
/**
* _realloc - reallocates a memory block using malloc and free
* @ptr: pointer to the memory previsouly allocated by malloc
* @old_size: size of the allocated memory f
* @new_size: new size of the new memory block
*
* Return: pointer to the newly allocated memory block
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *ptr1;
	char *old_ptr;
	unsigned int i;

	if (new_size == old_size)
	return (ptr);
	if (new_size == 0 && ptr)
	{
	free(ptr);
	return (NULL);
	}
	if (!ptr)
	return (malloc(new_size));
	ptr1 = malloc(new_size);
	if (!ptr1)
	return (NULL);
	old_ptr = ptr;
	if (new_size < old_size)
	{
	for (i = 0; i < new_size; i++)
	ptr1[i] = old_ptr[i];
	}
	if (new_size > old_size)
	{
	for (i = 0; i < old_size; i++)
	ptr1[i] = old_ptr[i];
	}
	free(ptr);
	return (ptr1);
}
