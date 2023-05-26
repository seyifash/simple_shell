#include "shell.h"
/**
* print_prompt1 - prints the prompt for user
*
*/
void print_prompt1(void)
{
write(STDOUT_FILENO, "$ ", 2);
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
int i;
if (ptr == NULL)
return;
for (i = 0; ptr[i] != NULL; i++)
{
free(ptr[i]);
}
free(ptr);
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
