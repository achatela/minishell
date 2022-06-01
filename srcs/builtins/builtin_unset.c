/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:44:05 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/01 16:56:36 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cut_var_modif(char *str, int j)
{
	char	*ret;

	ret = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!ret)
		return (NULL);
	while (str[j] && str[j] != '=')
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '=';
	ret[j + 1] = '\0';
	return (ret);
}

char	**remove_var(char **env, char *tmp, int i, int j)
{
	char	**new;
	int		k;

	new = malloc(sizeof(char *) * (env_lines(g_env)));
	if (!new)
		return (NULL);
	while (g_env[++i] != 0)
	{
		k = -1;
		if (ft_strncmp(tmp, g_env[i], ft_strlen(tmp)) != 0)
		{
			new[j] = malloc(sizeof(char) * (ft_strlen(g_env[i]) + 1));
			while (g_env[i][++k])
				new[j][k] = g_env[i][k];
			new[j][k] = '\0';
			j++;
		}
	}
	new[j] = 0;
	free_env(env, 0);
	return (new);
}

/*char	*search_env(char *str, int i, int j)
  {
  char	*ret;

  while (str[i] && str[i] != '=')
  i++;
  if (str[i] == '\0')
  return (NULL);
  ret = malloc(sizeof(char) * i + 2);
  if (!ret)
  return (NULL);
  while (str[j] != '=')
  {
  ret[j] = str[j];
  j++;
  }
  ret[j] = '\0';
  return (ret);
  }*/

int	check_name(char *str, t_args *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]))
	{
		printf("unset: `%s': not a valid identifier\n", args->parsed_arg);
		builtin_export(g_env, ft_export(1, "export"));
		return (1);
	}
	while (str[++i])
	{
		if (!(str[i] && (ft_isalpha(str[i]) == 1 || ft_isalnum(str[i]) == 1
					|| str[i] == '_')))
		{
			printf("unset: `%s': not a valid identifier\n", args->parsed_arg);
			builtin_export(g_env, ft_export(1, "export"));
			return (1);
		}
	}
	return (0);
}

void	builtin_unset(char **env, t_args *args)
{
	int		i;
	char	*tmp;

	(void)env;
	while (args->next != NULL && args->next->to_use == 1
		&& args->next->is_separator != 1)
	{
		args = args->next;
		if (check_name(args->parsed_arg, args) == 0)
		{
			tmp = cut_var_modif(args->parsed_arg, 0);
			i = -1;
			while (g_env[++i] != 0)
			{
				if (ft_strncmp(tmp, g_env[i], ft_strlen(tmp)) == 0)
				{
					g_env = remove_var(g_env, tmp, -1, 0);
					break ;
				}
			}
			free(tmp);
		}
	}
}
