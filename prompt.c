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
