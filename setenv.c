#include "shell.h"
/**
* new_var - creates a new environmental variable
* @name: name of the environmental variable to set
* @value: value to which the environmental variable is to be set
* Return: returns the new environmental variable
*/
char *new_var(char *name, char *value)
{
size_t len_name = _strlen(name);
size_t len_value = _strlen(value);
size_t len_total = 0;
char *new_env;
size_t i;
size_t j;
len_total = len_name + len_value + 2;
new_env = (char *)malloc(len_total *sizeof(char));
if (new_env == NULL)
{
return (NULL);
}
for (i = 0; i < len_name; i++)
{
new_env[i] = name[i];
}
new_env[i++] = '=';
for (j = 0; j < len_value; j++, i++)
{
new_env[i] = value[j];
}
new_env[i] = '\0';
return (new_env);
}
/**
* _setenv - sets a new environmental variable
* @name: name of the variable
* @value: the value to be updated
* @overwrite: second argument passed to the command
* Return: returns 0 on success
*/
int _setenv(char *name, char *value, int overwrite)
{
char **new_environ;
int envc;
int i;
if (name == NULL || value == NULL)
{
write(STDERR_FILENO, "Error: Invalid arguments\n", 25);
return (-1);
}
if (find_exist(name, value, overwrite) == -1)
{
envc = 0;
while (environ[envc] != NULL)
{
envc++;
}
new_environ = malloc((envc + 2) * sizeof(char *));
if (new_environ == NULL)
{
write(STDERR_FILENO, "Error: Memory allocation failed\n", 32);
return (-1);
}
for (i = 0; i < envc; i++)
{
new_environ[i] = environ[i];
}
new_environ[envc++] = new_var(name, value);
new_environ[envc] = NULL;
environ = new_environ;
free(new_environ[envc]);
return (0);
}
return (0);
}
/**
* find_exist - finds if the variable already exists
* @name: variable name
* @value: the value to be set to the existing variable
* @overwrite: flag indicating whether to overwrite the existing variable
* Return: returns 0 on success
*/
int find_exist(char *name, char *value, int overwrite)
{
char *env;
size_t len_name = _strlen(name);
char **dupenv = environ;

while (*dupenv != NULL)
{
if (_strncmp(name, *dupenv, len_name) == 0 && (*dupenv)[len_name] == '=')
{
if (overwrite)
{
env = new_var(name, value);
*dupenv = env;
free(env);
return (0);
}
else
{
return (-1);
}
}
dupenv++;
}
return (-1);
}
