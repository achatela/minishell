/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:16:51 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/13 16:44:53 by achatela         ###   ########.fr       */
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

char	*full_path(t_args *args)
{
	if (simple_path(args->next->parsed_arg) == 0)
		return (getenv("HOME"));
	else if (simple_path(args->next->parsed_arg) == 2)
		return (parsed_path(args->next->parsed_arg, 0, 0));
	return (NULL);
}

int	builtin_cd(t_args *args, int i)
{
	char	*tmp;

	tmp = NULL;
	if (args->next)
		tmp = args->next->parsed_arg;
	if (args->next != NULL && args->next->is_separator == 0
		&& args->next->next != NULL && args->next->next->is_separator == 0)
		return (printf("cd: too many arguments\n"), 1);
	if (args->next != NULL && args->next->is_separator == 0)
	{
		tmp = parsed_path(args->next->parsed_arg, 0, 0);
		if (simple_path(args->next->parsed_arg) != 2
			&& chdir(args->next->parsed_arg) == 0)
		{
			switch_pwds(g_env, 0, 0);
			free(tmp);
			args->echo->print = 0;
			return (0);
		}
		else if (simple_path(args->next->parsed_arg) == 2)
			simple_path_return(args, tmp, i);
	}
	return (cd_end(args, tmp));
}
