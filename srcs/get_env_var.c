/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:24:42 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/02 16:25:02 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_var_end(char *str, int i, int j)
{
	int		k;
	char	*ret;

	while (str[i] != '=')
		i++;
	k = i;
	while (str[++i])
		j++;
	ret = malloc(sizeof(char) * j + 1);
	j = 0;
	while (str[++k])
	{
		ret[j] = str[k];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*get_env_var(char **env, char *var, int i)
{
	char	*ret;

	(void)env;
	while (g_env[i] != 0)
	{
		if (var == NULL)
			break ;
		if (ft_strncmp(g_env[i], var, ft_strlen(var)) == 0)
			return (cut_var_end(g_env[i], 0, 0));
		i++;
	}
	ret = malloc(sizeof(char));
	ret[0] = '\0';
	return (ret);
}
