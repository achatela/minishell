/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:07:37 by achatela          #+#    #+#             */
/*   Updated: 2022/05/17 17:16:13 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*home_path(t_args *args)
{
	char	*path;

	path = full_path(args);
	if (path == NULL)
		return (NULL);
	return (path);
}

int	print_cd_errors(char *tmp, char *home, t_args *args)
{
	if (tmp != NULL && ft_check_access(tmp, 1) != 0)
		return (1);
	home = get_env_var(g_env, "HOME", 0);
	if (home == NULL && args->next == NULL)
		return (printf("cd: HOME not set\n"), 1);
	if (access(home, R_OK) == -1)
	{
		printf("%s: No such file or directory\n", tmp);
		return (free(home), 1);
	}
	if (tmp == NULL || (args->next && args->is_separator == 1))
	{
		chdir(home);
		free(home);
		return (1);
	}
	free(home);
	return (0);
}

int	cd_errors(t_args *args, char *tmp, char	*home)
{
	if (print_cd_errors(tmp, home, args) == 1)
		return (1);
	home = get_env_var(g_env, "HOME", 0);
	if (args->next == NULL
		|| (args->next != NULL && args->next->parsed_arg[0] == '~')
		|| (args->next != NULL && args->next->is_separator == 1))
	{
		if (args->next == NULL || home_path(args) == NULL)
			chdir(home);
		else if (home_path(args) != NULL)
		{
			if (chdir(tmp) == 0)
				chdir(home_path(args));
		}
		free(home);
		switch_pwds(g_env, 0, 0);
		return (1);
	}
	printf("%s: Not a directory\n", tmp);
	free(home);
	return (1);
}

void	cd_end(t_args *args, char *tmp, int i)
{
	(void)tmp;
	if (args->next)
		tmp = args->next->parsed_arg;
	if (args->next == NULL)
		builtin_export(g_env, ft_export(i, "export"));
	else
		builtin_export(g_env, ft_export(i, "export"));
	switch_pwds(g_env, 0, 0);
}

int	simple_path_return(t_args *args, char *tmp, int i)
{
	if (chdir(tmp) == 0)
	{
		switch_pwds(g_env, 0, 0);
		free(tmp);
		builtin_export(g_env, ft_export(0, "export"));
		return (0);
	}
	else
	{
		i = cd_errors(args, tmp, "");
		free(tmp);
		builtin_export(g_env, ft_export(i, "export"));
		return (i);
	}
}
