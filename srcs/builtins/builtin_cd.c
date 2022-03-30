#include "minishell.h"

//à refaire pour gérer "cd ~///////dossier_valide///

static int	simple_path(char *arg)
{
	if (arg == NULL)
		return (1);
	if (arg[0] && arg[1])
	{
		if (arg[0] == '~')
		{
			if (arg[1] == '/')
				return (0);
			else if (arg[1] == '\0')
				return (0);
		}
	}
	else if (arg[0])
		return (0);
	return (1);
}

static char	*full_path(char **cmds)
{
//	char	*path;

	if (simple_path(cmds[1]) == 0)
		return (getenv("HOME"));
	/*path = cd_paths(cmds[1]);
	if (path != NULL)
		return (path);*/
	return (NULL);
}

static char	*home_path(char **cmds)
{
	char	*path;

	path = full_path(cmds);
	if (path == NULL)
		return (NULL);
	return (path);
}

static int	cd_errors(char **cmds)
{
	if (cmds[1] == NULL || (cmds[1][0] == '~'))
	{
		if (cmds[1] == NULL || home_path(cmds) == NULL)
		{
			chdir(getenv("HOME"));
			return (1);
		}
		else if (home_path(cmds) != NULL)
			chdir(home_path(cmds));
		return (1);
	}
	if (access(cmds[1], F_OK) == -1)
	{
		printf("cd: %s: No such file or directory\n", cmds[1]);
		return (1);
	}
	if (access(cmds[1], R_OK) == -1)
	{
		printf("cd: %s: Permission denied\n", cmds[1]);
		return (1);
	}
	printf("cd: %s: Not a directory\n", cmds[1]);
	return (1);
}

int	builtin_cd(char **cmds, int i)
{
	char	*path;

	path = NULL;
	(void)path;
	while (cmds[i] != NULL)
		i++;
	if (path == NULL && i > 2)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (cmds[1] != NULL)
	{
	//	path = cd_paths(cmds[1]);
		if (!chdir(cmds[1]))
			return (0);
	}
	return(cd_errors(cmds));
}
