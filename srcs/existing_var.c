/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existing_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:22:23 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/08 16:23:36 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exact_copy(char **env, t_args *args)
{
	int		i;
	int		length;

	(void)env;
	i = 0;
	while (g_env[i] != 0)
	{
		length = ft_strlen(g_env[i]);
		if (ft_strlen(args->parsed_arg) > length)
				length = ft_strlen(args->parsed_arg);
		if (ft_strncmp(g_env[i], args->parsed_arg, length) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	var_existing(char *tmp, int i)
{
	char	*tmp2;

	while (g_env[i] != 0)
	{
		tmp2 = cut_var_modif(g_env[i], 0);
		if (ft_strncmp(tmp, tmp2, ft_strlen(tmp)) == 0)
		{
			g_env = remove_var(g_env, tmp, -1, 0);
			free(tmp);
			free(tmp2);
			return (1);
		}
		free(tmp2);
		i++;
	}
	free(tmp);
	return (0);
}

int	existing_var(char **env, t_args *args)
{
	char	*tmp;
	int		i;

	i = 0;
	(void)env;
	tmp = cut_var_modif(args->parsed_arg, 0);
	if (tmp == NULL)
		tmp = ft_strdup(args->parsed_arg);
	if (exact_copy(g_env, args) == 1)
	{
		free(tmp);
		return (2);
	}
	var_existing(tmp, i);
	return (0);
}
