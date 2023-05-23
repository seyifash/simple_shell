#include "shell.h"
/**
* _strlen - returns the length of a string
* @s: length of string to be returned
* Return: returns length
*/
int _strlen(char *s)
{
int len = 0;
while (*s != '\0')
{
len++;
s++;
}
return (len);
}
/**
* _strcpy - copies the string pointed to by src
* @dest: destination
* @src: source
* Return: string
*/
char *_strcpy(char *dest, char *src)
{
int len = 0;
while (*(src + len) != '\0')
{
*(dest + len) = *(src + len);
len++;
}
*(dest + len) = '\0';
return (dest);
}
/**
* _strcat - concatenates two string
* @dest: copy to
* @src: copy from
* Return: pointer to dest
*/
char *_strcat(char *dest, char *src)
{
int i = 0;
int j = 0;
while (dest[i] != '\0')
{
i++;
}
while (src[j] != '\0')
{
dest[i] = src[j];
i++;
j++;
}
dest[i] = '\0';
return (dest);
}
/**
* _memset - funtion that fills memory with a constant byte
* @s: starting address of memory to be filled
* @b: the desierd value
* @n:number of bytes to be changed
*
* Return: changed array with new value for n bytes
*/
char *_memset(char *s, char b, unsigned int n)
{
int i = 0;
for (; n > 0; i++)
{
s[i] = b;
n--;
}
return (s);
}
/**
* _strdup - a function that returns a pointer to a newly allocated string
* @str: the string to be duplicated
* Return: return pointer to the duplicatd string
*/
char *_strdup(char *str)
{
int f;
int i;
char *arr;
if (str == NULL)
return (NULL);
i = 0;
while (str[i] != '\0')
i++;
arr = malloc(sizeof(char) * (i + 1));
if (arr == NULL)
return (NULL);
for (f = 0; str[f]; f++)
arr[f] = str[f];
arr[f] = '\0';
return (arr);
}
