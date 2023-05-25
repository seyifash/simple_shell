#include "shell.h"
/**
* _strchr - function checks for the first occurrence of a character in a string
* @str: the string to be searched
* @c: the character to search
*
* Return: returns remaining portion of string if found else NULL
*/
char *_strchr(const char *str, int c)
{
while (*str != '\0')
{
if (*str == c)
return ((char *)(str));
str++;
}
return (NULL);
}
/**
* _strstr - searches for the first occurrence of a string in another string
* @haystack: the string in which the search occurs
* @needle: the string to be searched for
*
* Return: returns the substring if the needle is found else NULL
*/
char *_strstr(const char *haystack, const char *needle)
{
int i, j;
for (i = 0; haystack[i] != '\0'; i++)
{
j = 0;
while (needle[j] != '\0' && haystack[i + j] == needle[j])
{
j++;
}
if (needle[j] == '\0')
{
return ((char *)&haystack[i]);
}
}
return (NULL);
}
