#include "shell.h"
struct AliasData
{
char aliases[ALEN][VLEN];
char values[ALEN][VLEN];
int aliasCount;
};
void all_aliases(const struct AliasData *data);
int aliasfunc(struct AliasData *data, char **token,
int status, char *filename);
void setalias(struct AliasData *data, char **tokens);
void aliasvalue(const struct AliasData *data, char *aliasName);
void all_aliases(const struct AliasData *data)
{
char output[1000];
int i;
for (i = 0; i < aliasCount; i++)
{
_strcat(output, aliases[i]);
_strcat(output, "=");
_strcat(output, values[i]);
_strcat(output, "\n");
}
write(STDOUT_FILENO, output, strlen(output));
}
/**
* aliasfunc - checks for argument after the alias command
* @token: the command entered
* @status: unused
* @filename: unused
* Return: returns 0 on success
*/
int aliasfunc(char **token, int status, char *filename)
{
int i;
(void)status;
(void)filename;
if (token[0] == NULL)
{
all_aliases();
return (0);
}
else if (token[1] != NULL && _strchr(token[1], '='))
{
setalias(token);
return (0);
}
else
{
i = 1;
while (token[i] != NULL)
{
aliasvalue(token[i]);
i++;
return (0);
}
}
return (-1);
}
/**
* setalias - sets the alias if there's a given value
* @tokens: the command entered
*/
void setalias(char **tokens)
{
int i;
char *name = _strtok(tokens[1], "=");
char *value = _strtok(NULL, "=");
if (name != NULL && value != NULL)
{
for (i = 0; i < aliasCount; i++)
{
if (_strcmp(aliases[i], name) == 0)
{
_strcpy(values[i], value);
return;
}
}
if (aliasCount < ALEN)
{
_strcpy(aliases[aliasCount], name);
_strcpy(values[aliasCount], value);
aliasCount++;
}
}
}
/**
* aliasvalue - checks for the value assigned to a name
* @aliasName: the name for the alias to be checked
*/
void aliasvalue(char *aliasName)
{
char *aliasValue = NULL;
char output[ALEN + VLEN + 2];
int i;
for (i = 0; i < aliasCount; i++)
{
if (_strcmp(aliases[i], aliasName) == 0)
{
aliasValue = values[i];
break;
}
}
if (aliasValue != NULL)
{
_strcpy(output, aliasName);
_strcat(output, "=");
_strcat(output, aliasValue);
write(STDOUT_FILENO, output, strlen(output));
write(STDOUT_FILENO, "\n", 1);
}
}
