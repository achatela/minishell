/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:16:51 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/07 16:13:14 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	simple_path(char *arg)
{
	if (arg == NULL)
		return (1);
	if (arg[0])
	{
		if (arg[0] == '~')
		{
			if (arg[1] == '/' && arg[2] == '\0')
				return (2);
			else if (arg[1] == '\0')
				return (2);
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
	if (simple_path(args->next->parsed_arg) == 0)
		return (getenv("HOME"));
	else if (simple_path(args->next->parsed_arg) == 2)
		return (parsed_path(args->next->parsed_arg, 0, 0));
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

static int	cd_errors(t_args *args, char *tmp, char	*home)
{
	if (tmp != NULL && ft_check_access(tmp, 1) != 0)
		return (1);
	home = get_env_var(g_env, "HOME", 0);
	if (home == NULL && args->next == NULL)
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	if (tmp == NULL || (args->next && args->is_separator == 1))
	{
		chdir(home);
		free(home);
		return (1);
	}
	if (args->next == NULL
		|| (args->next != NULL && args->next->parsed_arg[0] == '~')
		|| (args->next != NULL && args->next->is_separator == 1))
	{
		if (args->next == NULL || home_path(args) == NULL)
		{
			chdir(home);
			free(home);
			switch_pwds(g_env, 0, 0);
			return (1);
		}
		else if (home_path(args) != NULL)
		{
			if (chdir(tmp) == 0)
			{
				chdir(home_path(args));
				free(home);
				switch_pwds(g_env, 0, 0);
				return (1);
			}
		}
	}
	printf("cd: %s: Not a directory\n", tmp);
	free(home);
	return (1);
}

int	builtin_cd(t_args *args, int i)
{
	char	*tmp;

	tmp = NULL;
	if (args->next)
		tmp = args->next->parsed_arg;
//	else
//		tmp = parsed_path(args->next->parsed_arg, 0, 0);
	if (args->next != NULL && args->next->is_separator == 0
		&&  args->next->next != NULL && args->next->next->is_separator == 0)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (args->next != NULL && args->next->is_separator == 0)
	{
		tmp = parsed_path(args->next->parsed_arg, 0, 0);
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
				i = cd_errors(args, tmp, "");
				free(tmp);
				return (i);
			}
		}
	}
	if (args->next)
		tmp = args->next->parsed_arg;
	if (args->next != NULL && simple_path(args->next->parsed_arg) == 2)
		i = cd_errors(args, tmp, "");
	else if (args->next == NULL)
		i = cd_errors(args, NULL, "");
	else
		i = cd_errors(args, tmp, "");
	switch_pwds(g_env, 0, 0);
	return (i);
}
