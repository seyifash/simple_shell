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
*_realloc - reallocates a memory block using malloc and free
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
