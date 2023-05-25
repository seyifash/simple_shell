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
/**
* _getenv - get the value of an environmental variable
* @name: the variable name
*
* Return: the value of name
*/
char *_getenv(const char *name)
{
int i = 0, j = 0;
while (environ[i])
{
while (environ[i][j] && *name)
{
if (environ[i][j] != *name || (environ[i][j] == '='))
break;
j++, name++;
}
if (environ[i][j] == '=' && !*name)
return ((environ[i] + ++j));
i++;
}
return (0);
}
/**
* getlocation - gets the path of a command
* @command: the command whose path is to be checked
*
* Return: returns the cmd path on success, NULL on failure
*/
char *getlocation(char *command)
{
char *path, *path_copy, *path_token, *file_path;
int command_length, directory_length;
struct stat buffer;
path = _getenv("PATH");
if (path)
{
path_copy = _strdup(path);
command_length = _strlen(command);
path_token = strtok(path_copy, ":");
while (path_token != NULL)
{
directory_length = _strlen(path_token);
file_path = malloc(command_length + directory_length + 2);
_strcpy(file_path, path_token);
_strcat(file_path, "/");
_strcat(file_path, command);
_strcat(file_path, "\0");
if (stat(file_path, &buffer) == 0)
{
free(path_copy);
return (file_path);
}
else
{
free(file_path);
path_token = strtok(NULL, ":");
}
}
free(path_copy);
if (stat(command, &buffer) == 0)
{
return (command);
}
return (NULL);
}
return (NULL);
}

