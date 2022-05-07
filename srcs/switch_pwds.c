/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_pwds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:43:58 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/07 16:28:48 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_pwd(char *str, int i)
{
	char	*ret;

	ret = malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!ret)
		return (NULL);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '=';
	ret[i + 1] = '\0';
	return (ret);
}

static char	**copy_env2(char **env, char *str, int i, int j)
{
	char	**new;

	new = malloc(sizeof(char *) * (env_lines(env) + 1));
	while (env[i] != 0)
	{
		j = 0;
		new[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!new)
			return (NULL);
		while (env[i][j])
		{
			new[i][j] = env[i][j];
			j++;
		}
		new[i][j] = '\0';
		i++;
	}
	new[i] = create_pwd(str, 0);
	new[i + 1] = 0;
	free_env(env, 0);
	return (new);
}

static char	*new_pwd(char *env, char *str, char *str2)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	free(env);
	if (str)
		j += ft_strlen(str);
	if (str2)
		j += ft_strlen(str2);
	env = malloc(sizeof(char) * (j + 1));
	j = 0;
	if (!env)
		return (NULL);
	if (str)
	{
		while (str[++i])
			env[i] = str[i];
	}
	if (str2)
	{
		while (str2[j])
		{
			env[i] = str2[j];
			i++;
			j++;
		}
	}
	env[i] = '\0';
	return (env);
}

void	switch_pwds(char **env, int i, int j)
{
	char	*tmp;

	while (env[i] != 0 && ft_strncmp(env[i], "PWD=", 4) != 0)
		i++;
	while (env[j] != 0 && ft_strncmp(env[j], "OLDPWD=", 7) != 0)
		j++;
	if (env[i] == 0 || env[j] == 0)
	{
		if (g_env[i] == 0)
			g_env = copy_env2(g_env, "PWD", 0, 0);
		if (g_env[j] == 0)
			g_env = copy_env2(g_env, "OLDPWD", 0, 0);
	}
	else
	{
		tmp = get_env_var(g_env, "PWD", 0);
		env[j] = new_pwd(env[j], "OLDPWD=", tmp);
		free(tmp);
		tmp = getcwd(NULL, 0);
		env[i] = new_pwd(env[i], "PWD=", tmp);
		free(tmp);
	}
}
