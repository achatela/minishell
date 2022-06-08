/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:07:37 by achatela          #+#    #+#             */
/*   Updated: 2022/06/08 17:37:23 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*home_path(t_args *args)
{
	char	*path;

	path = full_path(args);
	if (!path)
		return (NULL);
	return (path);
}

int	print_cd_errors(char *tmp, char *home, t_args *args)
{
	char	*check;

	check = home_path(args);
	if (check != NULL && ft_check_access(check, 0) != 0)
		return (free(check), 1);
	free(check);
	home = get_env_var(g_env, "HOME", 0);
	if (home == NULL && args->next == NULL)
		return (printf("cd: HOME not set\n"), 1);
	if (access(home, R_OK) == -1)
	{
		printf("%s: No such file or directory\n", tmp);
		return (free(home), 1);
	}
	if (tmp == NULL || (args->next && args->is_separator == 1))
		return (chdir(home), free(home), 1);
	return (free(home), 0);
}

int	cd_errors(t_args *args, char *tmp, char	*home, char *tmp2)
{
	tmp2 = home_path(args);
	if (print_cd_errors(tmp, home, args) == 1)
	{
		free(tmp2);
		return (1);
	}
	home = get_env_var(g_env, "HOME", 0);
	if (args->next == NULL
		|| (args->next != NULL && args->next->parsed_arg[0] == '~')
		|| (args->next != NULL && args->next->is_separator == 1))
	{
		if (args->next == NULL || tmp2 == NULL)
			chdir(home);
		else if (tmp2 != NULL)
		{
			if (chdir(tmp) == 0)
				chdir(tmp2);
			free(tmp2);
		}
		free(home);
		switch_pwds(g_env, 0, 0);
		return (1);
	}
	error_path(args, tmp, tmp2, home);
	return (1);
}

void	cd_end(t_args *args, char *tmp)
{
	if (args->next == NULL)
		builtin_export(g_env,
			ft_export(cd_errors(args, NULL, "", ""), "export"));
	else
	{
		if (args->next)
		{
			tmp = args->next->parsed_arg;
			builtin_export(g_env,
				ft_export(cd_errors(args, tmp, "", ""), "export"));
		}
		else
		{
			builtin_export(g_env,
				ft_export(cd_errors(args, tmp, "", ""), "export"));
		}
	}
	switch_pwds(g_env, 0, 0);
}

int	simple_path_return(t_args *args, char *tmp)
{
	int	i;

	i = 0;
	if (chdir(tmp) == 0)
	{
		switch_pwds(g_env, 0, 0);
		builtin_export(g_env, ft_export(0, "export"));
		return (0);
	}
	else
	{
		i = cd_errors(args, tmp, "", "");
		builtin_export(g_env, ft_export(i, "export"));
		free(tmp);
		return (i);
	}
}
