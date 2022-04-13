#include "minishell.h"

/*	Manque gestion cd $var inexistante 
	et c'est la merde*/

static int	simple_path(char *arg)
{
	if (arg == NULL)
		return (1);
	if (arg[0] && arg[1])
	{
		if (arg[0] == '~')
		{
			if (arg[1] == '/' && arg[2] == '\0')
				return (0);
			else if (arg[1] == '\0')
				return (0);
			else
				return (2);
		}
	}
	else if (arg[0])
		return (0);
	return (1);
}

static char	*parsed_path(char *str, int i, int j)
{
	char	*ret;
	char	*tmp;

	if (simple_path(str) != 2)
		return (NULL);
	tmp = get_env_var(g_env, "HOME=", 0);
	ret = malloc(sizeof(char) * (ft_strlen(tmp) + ft_strlen(str) + 1));
	while (tmp[i])
		ret[j++] = tmp[i++];
	i = 1;
	while (str[i])
		ret[j++] = str[i++];
	ret[j] = '\0';
	free(tmp);
	return (ret);
}

static char	*full_path(t_args *args)
{
//	char	*path;

	if (simple_path(args->next->parsed_arg) == 0)
		return (getenv("HOME"));
	else if (simple_path(args->next->parsed_arg) == 2)
		return (parsed_path(args->next->parsed_arg, 0, 0));
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

static int	cd_errors(t_args *args, char *tmp)
{
	if (tmp == NULL || (args->next && args->is_separator == 1))
	{
		chdir(getenv("HOME"));
		return (1);
	}
	if (access(tmp, F_OK) == -1)
	{
		printf("cd: %s: No such file or directory\n", tmp);
		return (1);
	}
	else if (access(tmp, R_OK) == -1)
	{
		printf("cd: %s: Permission denied\n", tmp);
		return (1);
	}
	if (args->next == NULL /*|| (args->next != NULL && args->next->parsed_arg == NULL)
		*/|| (args->next != NULL && args->next->parsed_arg[0] == '~')
		|| (args->next != NULL && args->next->is_separator == 1))
	{
		if (args->next == NULL || home_path(args) == NULL)
		{
			chdir(getenv("HOME"));
			switch_pwds(g_env, 0, 0);
			return (1);
		}
		else if (home_path(args) != NULL)
		{
			if (chdir(tmp) == 0)
			{
				chdir(home_path(args));
				switch_pwds(g_env, 0, 0);
				return (1);
			}
		}
	}
	printf("cd: %s: Not a directory\n", tmp);
	return (1);
}

int	builtin_cd(t_args *args, int i)
{
	char	*tmp;

	tmp = NULL;
	if (tmp != NULL)	/* tmp = pour free home path dans cd errors + gérer ~////dossier_valid// */
		return (2);
	if (args->next != NULL && args->next->is_separator == 0
		&&  args->next->next != NULL && args->next->next->is_separator == 0)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (args->next != NULL && args->next->is_separator == 0)
	{
		tmp = parsed_path(args->next->parsed_arg, 0, 0);
	//	path = cd_paths(cmds[1]);
		if (simple_path(args->next->parsed_arg) != 2 && chdir(args->next->parsed_arg) == 0)
		{
			switch_pwds(g_env, 0, 0);
			free(tmp);
			return (0);
		}
		else if (simple_path(args->next->parsed_arg) == 2)
		{
			if (chdir(tmp) == 0)
			{
				switch_pwds(g_env, 0, 0);
				free(tmp);
				return (0);
			}
			else
			{
				i = cd_errors(args, tmp);
				free(tmp);
				return (i);
			}
		}
	}
	if (args->next != NULL && simple_path(args->next->parsed_arg) == 2)
		i = cd_errors(args, tmp);
	else if (args->next == NULL)
		i = cd_errors(args, NULL);
	else
		i = cd_errors(args, NULL);
	switch_pwds(g_env, 0, 0);
	if (tmp != NULL)
		free(tmp);
	return (i);
}
