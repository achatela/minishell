/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:25:15 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/04 12:23:15 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//home < pwd home > pwd home == pwd

static char	*get_session(char **env, int i, int j, int k)
{
	char	*tmp;
	char	*ret;

	(void)env;
	tmp = get_env_var(g_env, "SESSION_MANAGER", 0);
	if (!tmp)
		return (NULL);
	while (tmp[i] && tmp[i] != '/')
		i++;
	j = i;
	while (tmp[i] && tmp[++i] != '.')
		k++;
	ret = malloc(sizeof(char) * k + 3);
	i = 1;
	ret[0] = '@';
	while (tmp[j] && tmp[++j] != '.')
	{
		ret[i] = tmp[j];
		i++;
	}
	ret[i] = ':';
	ret[i + 1] = '\0';
	free(tmp);
	return (ret);
}

static char	*fill_tmp(char *tmp, int i)
{
	if (i == 0)
	{
		tmp = malloc(sizeof(char) * 2);
		tmp[0] = '~';
		tmp[1] = '\0';
	}
	else if (i > 0)
		tmp = getcwd(NULL, 0);
	else if (i < 0)
	{
		tmp = malloc(sizeof(char) * 3);
		tmp[0] = '~';
		tmp[1] = '/';
		tmp[2] = '\0';
	}
	return (tmp);
}

static char	*get_home(char **env, int i, int j)
{
	char	*tmp;
	char	*tmp2;

	(void)j;
	(void)env;
	tmp = get_env_var(g_env, "HOME", 0);
	tmp2 = getcwd(NULL, 0);
	if (tmp && tmp2)
		i = ft_strncmp(tmp, tmp2, (ft_strlen(tmp) + 1));
	else
		i = 0;
	free(tmp);
	free(tmp2);
	tmp = fill_tmp(tmp, i);
	return (tmp);
}

char	*get_end(char **env, int i, int j)
{
	char	*tmp;
	char	*tmp2;
	int		k;

	k = 0;
	tmp = get_env_var(env, "HOME", 0);
	if (!tmp)
		return (NULL);
	tmp2 = getcwd(NULL, 0);
	while (tmp[i] == tmp2[i])
		i++;
	j = i - 1;
	free(tmp);
	while (tmp2[++i])
		k++;
	tmp = malloc(sizeof(char) * k + 2);
	k = 0;
	if (j > 0 && tmp2[j - 1] && tmp2[j] && tmp2[j] != '/')
		j++;
	while (j > 0 && tmp2[j - 1] && tmp2[j] && tmp2[++j])
	{
		tmp[k] = tmp2[j];
		k++;
	}
	tmp[k] = '\0';
	free(tmp2);
	return (tmp);
}

char	*get_prompt(char **env, int i)
{
	char	**ret;
	char	*tmp;

	tmp = malloc(sizeof(char));
	tmp[0] = '\0';
	ret = malloc(sizeof(char *) * 4);
	(void)get_session;
	(void)get_home;
	ret[0] = get_env_var(g_env, "USER", 0);
	ret[1] = get_session(g_env, 0, 0, 0);
	ret[2] = get_home(g_env, 0, 0);
	if(ret[0] == NULL || ret[1] == NULL || ret[2] == NULL || ret[3] == NULL)
	{
		tmp = ft_strjoin(tmp, "$ ");
		return (tmp);
	}
	else if (ret[2] != NULL && ft_strlen(ret[2]) != 2)
		ret[3] = NULL;
	else
		ret[3] = get_end(env, 0, 0);
	while (++i < 4 && ret[i] != NULL)
		tmp = ft_strjoin(tmp, ret[i]);
	tmp = ft_strjoin(tmp, "$ ");
	i = -1;
	while (++i < 4)
	{
		if (ret[i])
			free(ret[i]);
	}
	free(ret);
	return (tmp);
}
