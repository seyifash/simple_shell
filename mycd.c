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
	}

	if (_strcmp(dire, "-") == 0)
	{
	change_prevdir(cmd);
	}
	if (_strcmp(dire, ".") == 0)
	{
	current_dir(cmd);
	}
	else
	{
	change_givendir(cmd);
	}

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
	(void)cmd;

	getcwd(initial_dir, sizeof(initial_dir));

	prev_dir = _getenv("OLDPWD");
	if (prev_dir == NULL)
	{
	write(STDERR_FILENO, "Failed to get previous directory\n", 33);
	return;
	}
	_setenv("OLDPWD", initial_dir, 1);

	if (chdir(prev_dir) == -1)
	_setenv("PWD", initial_dir, 1);
	else
	_setenv("PWD", prev_dir, 1);
	p_pwd = _getenv("PWD");

	write(STDOUT_FILENO, p_pwd, strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	chdir(p_pwd);
}

/**
 * change_givendir - function that change to the given directory
 * @cmd: unused
 *
 */
void change_givendir(char **cmd)
{
	char pwd[BUFSIZE];
	char *dir, *cp_pwd, *cd_dir;
	(void)cmd;

	getcwd(pwd, sizeof(pwd));
	dir = cmd[1];
	if (dir == NULL)
	{
	perror("No directory provided");
	return;
	}
	dir = cmd[1];
	if (chdir(dir) == -1)
	{
	perror("chdir");
	return;
	}
	cp_pwd = _strdup(pwd);
	_setenv("OLDPWD", cp_pwd, 1);
	cd_dir = _strdup(dir);
	_setenv("PWD", cd_dir, 1);

	free(cp_pwd);
	free(cd_dir);

}

/**
 * current_dir - changes to the current directory
 * @cmd: unused
 *
 */
void current_dir(char **cmd)
{
	char pwd[BUFSIZE];
	char *cp_pwd;
	(void)cmd;

	getcwd(pwd, sizeof(pwd));

	cp_pwd = _strdup(pwd);
	_setenv("OLDPWD", cp_pwd, 1);
	free(cp_pwd);

	if (chdir(".") == -1)
	{
	perror("chdir");
	return;
	}

	getcwd(pwd, sizeof(pwd));
	_setenv("PWD", pwd, 1);
}
