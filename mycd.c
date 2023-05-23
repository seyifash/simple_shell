#include "shell.h"

/**
 * cd_cmd - a function that implements the cd buitin cmd
 * @cmd: the command given
 * @status: unused
 * @filename: unused
 * Return: return 1 on success and -1 on failure
 */
int cd_cmd(char **cmd, int status, char *filename)
{
	char *dire;
	int tilda, dash, home;
	(void)status;
	(void)filename;

	dire = cmd[1];
	if (dire != NULL)
	{
	home = _strcmp("$HOME", dire);
	dash = _strcmp("--", dire);
	tilda = _strcmp("~", dire);
	}

	if (dire == NULL || home || dash || tilda)
	{
	change_homedir(cmd);
	return (1);
	}

	if (_strcmp(dire, "..") == 0)
	{
	change_prevdir(cmd);
	return (1);
	}

	if (_strcmp(dire, "-") == 0)
	{
	change_prevdir(cmd);
	return (1);
	}
	if (_strcmp(dire, ".") == 0)
	{
	current_dir(cmd);
	return (1);
	}

	changeto_dir(cmd);

	return (1);

}

/**
 * change_homedir - change to the home directory
 * @cmd: unused
 *
 * Return: nothing
 */
void change_homedir(char **cmd)
{
	char *homedir, *dup_pwd;
	char initial_dir[BUFSIZE];
	(void)cmd;

	getcwd(initial_dir, sizeof(initial_dir));
	dup_pwd = _strdup(initial_dir);
	homedir = _getenv("HOME");
	if (homedir == NULL)
	{
	_setenv("OLDPWD", dup_pwd, 1);
	free(dup_pwd);
	return;
	}

	if (chdir(homedir) == -1)
	{
	write(STDERR_FILENO, "cd: Failed to change directory\n", 31);
	free(dup_pwd);
	return;
	}
	_setenv("OLDPWD", dup_pwd, 1);
	_setenv("PWD", homedir, 1);
	free(dup_pwd);
}

/**
 * change_prevdir - change from the current dir to the parent dir
 * @cmd: unused
 *
 * Return: nothing
 */
void change_prevdir(char **cmd)
{
	char *prev_dir, *p_pwd;
	char  initial_dir[BUFSIZE];
	char *cold_pwd, *cwd;
	(void)cmd;

	getcwd(initial_dir, sizeof(initial_dir));
	cwd = _strdup(initial_dir);

	prev_dir = _getenv("OLDPWD");
	if (prev_dir == NULL)

	cold_pwd = _strdup(cwd);
	else
	cold_pwd = _strdup(prev_dir);

	_setenv("OLDPWD", cwd, 1);

	if (chdir(prev_dir) == -1)
	_setenv("PWD", cwd, 1);
	else
	_setenv("PWD", cold_pwd, 1);
	p_pwd = _getenv("PWD");

	write(STDOUT_FILENO, p_pwd, strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cwd);
	if (prev_dir)
	free(cold_pwd);
	chdir(p_pwd);
}

/**
 * changeto_dir - changes to the specified directory
 * @cmd: the specified directory
 *
 */
void changeto_dir(char **cmd)
{
	char *dir = cmd[1];
	char pwd[BUFSIZE];
	char *cp_pwd, *newpwd;

	if (getcwd(pwd, BUFSIZE) == NULL)
	{
	perror("getcwd");
	return;
	}
	if (chdir(dir) != 0)
	{
	Errormes(cmd[0]);
	return;
	}
	cp_pwd = strdup(pwd);
	if (_setenv("OLDPWD", cp_pwd, 1) != 0)
	{
	perror("setenv");
	return;
	}
	newpwd = _strdup(dir);
	if (_setenv("PWD", newpwd, 1) != 0)
	{
	perror("setenv");
	return;
	}

	free(cp_pwd);
	free(newpwd);

}
/**
 * Errormes - prints error message
 * @command: the command
 *
 */
void Errormes(char *command)
{
	char error[100];

	strcpy(error, command);
	strcat(error, ": No such file or directory\n");
	write(STDOUT_FILENO, error, _strlen(error));
}
