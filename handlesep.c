#include "shell.h"
/**
 * execute - executes commands entered
 * @cmd: the command
 * @line: the commands entered
 *
 * Return: returns 0 on success
 */
int execute(char **cmd, char *line)
{
	char *cmdpath = NULL;
	int status;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
	cmdpath = getlocation(cmd[0]);
	if (cmdpath == NULL)
	{
	perror("Error");
	freememory_pp(cmd);
	free(line);
	exit(0);
	}
	else
	execve(cmdpath, cmd, environ);
	}
	else if (pid > 0)
	{
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
	}
	else
	{
	perror("Fork failed");
	return (-1);
	}

	freememory_pp(cmd);
	return (0);
}
/**
 * execmd - executes the command
 * @argv: the command to execute
 * Return: return 0 on success
 */
int execmd(char **argv)
{
	char *command = NULL;

	if (argv)
	{
	command = argv[0];
	if (execve(command, argv, NULL) == -1)
	{
	perror("./shell");
	freememory_pp(argv);
	exit(EXIT_FAILURE);
	}
	}
	freememory_pp(argv);
	return (0);
}
/**
 * splittoks - split commands into individuat strings
 * @line: the command to split
 *
 * Return: returns the tokenized string
 */
char **splittoks(char *line)
{
	char *token;
	char **toks;
	int numtoks = 0;
	char *delim = " \t\n\r\a";
	int i;
	char *cmd_cpy;

	cmd_cpy = _strdup(line);
	token = strtok(cmd_cpy, delim);
	while (token != NULL)
	{
	numtoks++;
	token = strtok(NULL, delim);
	}
	toks = malloc(sizeof(char *) * (numtoks + 1));
	token = strtok(line, delim);
	for (i = 0; token != NULL; i++)
	{
	toks[i] = malloc(sizeof(char) * (_strlen(token) + 1));
	strcpy(toks[i], token);
	token = strtok(NULL, delim);
	}
	toks[i] = NULL;
	free(cmd_cpy);
	return (toks);
}
/**
 * assign_line - assigns line
 * @lineptr: the buffer
 * @nl: size of what to read
 * @buffer: initial buffer
 * @jb: the total numberof chars read
 *
 */
void updateline(char **line, size_t *n, char *buffer, size_t chread)
{
	if (*line == NULL)
	{
	if (chread > BUFSIZE)
		*n = chread;
	else
	*n = BUFSIZE;
	*line = buffer;
	}
	else if (*n < chread)
	{
	if (chread > BUFSIZE)
	*n = chread;
	else
	*n = BUFSIZE;
	*line = buffer;
	}
	else
	{
	_strcpy(*line, buffer);
	free(buffer);
	}
}
/**
 * _getline - custom getline function
 * @lineptr: the line buffer
 * @nl: size of buffer to read
 * @strm: the file to read from
 * Return: returns the total number of chars read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *strm)
{
	int rd;
	static ssize_t chread;
	ssize_t totalr;
	char *buffer;
	char flow = 'z';

	if (chread == 0)
	fflush(strm);
	else
	return (-1);
	chread = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
	return (-1);
	while (flow != '\n')
	{
	rd = read(STDIN_FILENO, &flow, 1);
	if (rd == -1 || (rd == 0 && chread == 0))
	{
	free(buffer);
	return (-1);
	}
	if (rd == 0 && chread != 0)
	{
	chread++;
	break;
	}
	if (chread >= BUFSIZE)
	buffer = _realloc(buffer, chread, chread + 1);
	buffer[chread] = flow;
	chread++;
	}
	buffer[chread] = '\0';
	updateline(lineptr, n, buffer, chread);
	totalr = chread;
	if (rd != 0)
	chread = 0;
	return (totalr);
}
