/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:11:11 by achatela          #+#    #+#             */
/*   Updated: 2022/05/21 14:13:51 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_shlvl(char *str, int i, char *to_free)
{
	int		sh_lvl;
	char	*ret;
	char	*tmp;

	sh_lvl = ft_atoi(str + i) + 1;
	free(to_free);
	tmp = ft_itoa(sh_lvl);
	if (!tmp)
		return (NULL);
	ret = malloc(sizeof(char) * 7);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < 6)
		ret[i] = str[i];
	ret[i] = '\0';
	ret = ft_strjoin(ret, tmp);
	free(tmp);
	return (ret);
}

static char	**empty_env(char **env)
{
	env = malloc(sizeof(char *) * (2));
	env[0] = ft_strdup("SHLVL=1");
	env[1] = 0;
	return (env);
}

char	**init_envi(int *i, int k, char **env)
{
	int	tmp;

	while ((*i) < k)
	{
		g_env[(*i)] = malloc(sizeof(char) * (ft_strlen(env[(*i)]) + 1));
		if (!g_env[(*i)])
			return (NULL);
		if (ft_strlen(env[(*i)]) > 6)
			tmp = is_shlvl(env[(*i)]);
		if (tmp == 1)
			g_env[(*i)] = get_shlvl(env[(*i)], 6, g_env[(*i)]);
		else
		{
			free(g_env[(*i)]);
			g_env[(*i)] = ft_strdup(env[(*i)]);
		}
		(*i)++;
	}
	return (g_env);
}

char	**init_env(char **env, int i, int k)
{
	k = env_lines(env) - 1;
	if (k == 0)
		return (empty_env(NULL));
	g_env = malloc(sizeof(char *) * env_lines(env));
	if (!g_env)
		return (NULL);
	g_env = init_envi(&i, k, env);
	g_env[i] = 0;
	return (g_env);
}

char	*set_cmd(char *cmd, char *exit)
{
	int	i;

	i = -1;
	cmd = malloc(sizeof(char) * 5);
	while (exit[++i])
		cmd[i] = exit[i];
	cmd[i] = '\0';
	return (cmd);
}
