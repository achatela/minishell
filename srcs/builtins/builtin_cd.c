#include "minishell.h"

//à refaire pour gérer "cd ~///////dossier_valide///
/*static int	home_path(char **cmds)
{
	char	*path;
	char	*dir;

	path = getenv("HOME");
	dir = ft_strjoin(path, &cmds[1][1]);
	chdir(dir);
	return (1);
}*/

static int	cd_errors(char **cmds)
{
	if (cmds[1] == NULL || (cmds[1][0] == '~'
		&& cmds[1][1] == '\0') || (cmds[1][0] == '~'
		&& cmds[1][1] == '/' && cmds[1][2] == '\0'))
	{
		chdir(getenv("HOME"));
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
	while (cmds[i] != NULL)
		i++;
	if (i > 2)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (cmds[1] != NULL)
	{
		if (!chdir(cmds[1]))
			return (0);
	}
	return(cd_errors(cmds));
}
