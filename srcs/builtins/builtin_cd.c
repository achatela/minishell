/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:16:51 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/22 16:08:10 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_path(char *arg)
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

char	*parsed_path(char *str, int i, int j)
{
	char	*ret;
	char	*tmp;

	if (simple_path(str) != 2)
		return (NULL);
	tmp = get_env_var(g_env, "HOME", 0);
	if (tmp != NULL)
		ret = malloc(sizeof(char) * (ft_strlen(tmp) + ft_strlen(str) + 1));
	else
		ret = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (tmp != NULL)
	{
		while (tmp[i])
			ret[j++] = tmp[i++];
	}
	i = 1;
	while (str[i])
		ret[j++] = str[i++];
	ret[j] = '\0';
	free(tmp);
	return (ret);
}

char	*full_path(t_args *args)
{
	char	*tmp;

	if (args->next == NULL)
		return (NULL);
	tmp = parsed_path(args->next->parsed_arg, 0, 0);
	if (args == NULL || args->next == NULL)
	{
		free(tmp);
		return (NULL);
	}
	if (simple_path(args->next->parsed_arg) == 0)
	{
		free(tmp);
		return (getenv("HOME"));
	}
	else if (simple_path(args->next->parsed_arg) == 2)
		return (tmp);
	free(tmp);
	return (NULL);
}

void	builtin_cd2(t_args *args, char *tmp)
{
	if (args->next != NULL && args->next->is_separator == 0)
	{
		tmp = parsed_path(args->next->parsed_arg, 0, 0);
		if (simple_path(args->next->parsed_arg) != 2
			&& chdir(args->next->parsed_arg) == 0)
		{
			switch_pwds(g_env, 0, 0);
			free(tmp);
			builtin_export(g_env, ft_export(0, "export"));
			return ;
		}
		else if (simple_path(args->next->parsed_arg) == 2)
		{
			if (simple_path_return(args, tmp) == 0)
				free(tmp);
			return ;
		}
	}
	cd_end(args, tmp);
	free(tmp);
}

void	builtin_cd(t_args *args, char *tmp)
{
	if (args->next)
		tmp = args->next->parsed_arg;
	if (args->next != NULL && args->next->is_separator == 0
		&& args->next->next != NULL && args->next->next->is_separator == 0)
	{
		builtin_export(g_env, ft_export(1, "export"));
		printf("cd: too many arguments\n");
		return ;
	}
	builtin_cd2(args, tmp);
}
