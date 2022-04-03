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

static char	*full_path(t_args *args)
{
//	char	*path;

	if (simple_path(args->next->parsed_arg) == 0)
		return (getenv("HOME"));
	/*path = cd_paths(cmds[1]);
	if (path != NULL)
		return (path);*/
	return (NULL);
}

static char	*home_path(t_args *args)
{
	char	*path;

	path = full_path(args);
	if (path == NULL)
		return (NULL);
	return (path);
}

static int	cd_errors(t_args *args)
{
	if (args->next == NULL /*|| (args->next != NULL && args->next->parsed_arg == NULL)
		*/|| (args->next != NULL && args->next->parsed_arg[0] == '~')
		|| (args->next != NULL && args->next->is_separator == 1))
	{
		if (args->next == NULL || home_path(args) == NULL)
		{
			chdir(getenv("HOME"));
			return (1);
		}
		else if (home_path(args) != NULL)
			chdir(home_path(args));
		return (1);
	}
	if (access(args->next->parsed_arg, F_OK) == -1)
	{
		printf("cd: %s: No such file or directory\n", args->next->parsed_arg);
		return (1);
	}
	if (access(args->next->parsed_arg, R_OK) == -1)
	{
		printf("cd: %s: Permission denied\n", args->next->parsed_arg);
		return (1);
	}
	printf("cd: %s: Not a directory\n", args->next->parsed_arg);
	return (1);
}

int	builtin_cd(t_args *args, int i)
{
	if (args->next != NULL && args->next->is_separator == 0
		&&  args->next->next != NULL && args->next->next->is_separator == 0)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (args->next != NULL && args->next->is_separator == 0)
	{
	//	path = cd_paths(cmds[1]);
		if (chdir(args->next->parsed_arg) == 0)
			return (0);
	}
	i = cd_errors(args);
	return (i);
}
