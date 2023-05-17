#include "shell.h"

/**
 * _strncpy - copies a string with n
 * @dest: copy to
 * @src: copy from
 * @n: number
 * Return: number of char to be pointed to
 */

char *_strncpy(char *dest, char *src, int n)
{
	int j = 0;

	while (j < n && src[j] != '\0')
        {
	dest[j] = src[j];
	j++;
	}
	while (j < n)
	{
	dest[j] = '\0';
	j++;
	}
	return (dest);
}

/**
 * _putchar - prints a character to stdout
 * @c: the character given
 * Return: 1 if success, else -1.
 */

int _putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * print - prints a string to stdout
 * @str: the given string to be printed out
 *
 *
 * Return: the number of bytes of @str printed, else -1
 */
int print(char *str)
{
	int n_bytes = 0;

	n_bytes = _strlen(str);
	return (write(STDOUT_FILENO, str, n_bytes));
}

/**
 * _isalpha - checks if a character is a letter
 * @c: the given character
 *
 * Return: TRUE if true, else FALSE
 */

int _isalpha(char c)
{
	if ((c >= 48) && (c <= 57))
	return (FALSE);
	return (TRUE);
}

/**
 * _atoi - convert a string to an integer
 * @s:the string to be converted
 *
 * Return: int
 */
int _atoi(char *s)
{
	int len = 0;
	int i = 0;
	int flag = 0;
	int d = 0, n = 0, digit;

	for (len = 0; s[len] != '\0'; len++);

	while (i < len && flag == 0)
	{
	if (s[i] == '-')
	++d;
	if (s[i] >= 48 && s[i] <= 57)
	{
	digit = s[i] - '0';
	if (d % 2)
	digit = -digit;
	n = n * 10 + digit;
	flag = 1;
	if (s[i + 1] < 48 || s[i + 1] > 57)
	break;
	flag = 0;
	}
	i++;
	}
	if (flag == 0)
	return (0);

	return (n);
}
