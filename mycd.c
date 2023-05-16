#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1024

/**
 * cd_cmd - a function that implements the cd buitin cmd
 * @cmd: the command given
 * @status: number of argument
 * @filename: second argument to the command
 * Return: return 1 on success and -1 on failure
 */
int cd_cmd(char **cmd, int status, char *filename)
{
	char *dire;
	int tilda, dash, home;

	dire = cmd[1];
	if (dire != NULL)
	{
	home = strcmp("$HOME" dire);
	dash = strcmp("--", dire);
	tilda = strcmp("~", dire);
	}

	if (dire == NULL || home || dash || tilda)
	{
	change_homedir(cmd);
	return (1);
	}

	if (strcmp(dire, "..") == 0)
	{
	change_prevdir(cmd);
	}

	if (strcmp(dire, "-") == 0)
	{
	change_prevdir(cmd);
	}
	if (strcmp(dire, ".") == 0)
	{
	current_dir(cmd);
	}
	else
	{
	change_givendir(dire)
	}

	return (1);

}

/**
 * change_homedir - change to the home directory
 * @cmd: the given command
 *
 * Return: nothing
 */
void change_homedir(char **cmd)
{
	char *homedir;
	char *current_dir[BUFSIZE];
	char initial_dir[BUFSIZE];

	homedir = getenv("HOME");
	if (homedir == NULL)
	{
	write(STDERR_FILENO, "Failed to get home directory\n", 29);
	return;
	}
	if (getcwd(initial_dir, sizeof(initial_dir)) == NULL)
	{
	write(STDERR_FILENO, "Failed to get current directory\n", 32);
	return;
	}

	if (chdir(homedir) == -1)
	{
	write(STDERR_FILENO, "cd: Failed to change directory\n", 31);
	return;
	}
	setenv("OLDPWD", initial_dir, 1);
	setenv("PWD", homedir, 1);
}

/**
 * change_prevdir - change from the current dir to the parent dir
 * @cmd: the given command
 *
 * Return: nothing
 */
void change_prevdir(char **cmd)
{
	char *prev_dir, *p_pwd;
	char  initial_dir[BUFSIZE];

	getcwd(initial_dir, sizeof(initial_dir));

	prev_dir = getenv("OLDPWD");
	if (prev_dir == NULL)
	{
	write(STDERR_FILENO, "Failed to get previous directory\n", 33);
	return;
	}
	setenv("OLDPWD", initial_dir, 1);

	if (chdir(prev_dir) == -1)
	setenv("PWD", initial_dir, 1);
	else
	setenv("PWD", prev_dir, 1);
	p_pwd = getenv("PWD");

	write(STDOUT_FILENO, p_pwd, strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	chdir(p_pwd);
}

/**
 * change_givendir - function that change to the given directory
 * @cmd: command given
 *
 */
void change_givendir(char **cmd)
{
	char pwd[BUFSIZE];
	char *dir, *cp_pwd, *cd_dir;

	getcwd(pwd, sizeof(pwd));

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
	cp_pwd = strdup(pwd);
	setenv("OLDPWD", cp_pwd, 1);
	cd_dir = strdup(dir);
	setenv("PWD", cd_dir, 1);

	free(cp_pwd);
	free(cd_dir);

}

/**
 * current_dir - changes to the current directory
 * @cmd: command entered
 *
 */
void current_dir(char **cmd)
{
	char pwd[BUFSIZE];
	char *cp_pwd;

	getcwd(pwd, sizeof(pwd));

	cp_pwd = strdup(pwd);
	setenv("OLDPWD", cp_pwd, 1);
	free(cp_pwd);

	if (chdir(".") == -1)
	{
	perror("chdir");
	return;
	}

	getcwd(pwd, sizeof(pwd));
	setenv("PWD", pwd, 1);
}
