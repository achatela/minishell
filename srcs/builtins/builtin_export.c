/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:42:47 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/12 12:18:18 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*exported_var(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!ret)
		return (NULL);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static char	**copy_env(char **env, t_args *args, int i, int j)
{
	char	**new;

	new = malloc(sizeof(char *) * (env_lines(g_env) + 1));
	while (g_env[i] != 0)
	{
		j = 0;
		new[i] = malloc(sizeof(char) * (ft_strlen(g_env[i]) + 1));
		if (!new)
			return (NULL);
		while (g_env[i][j])
		{
			new[i][j] = g_env[i][j];
			j++;
		}
		new[i][j] = '\0';
		i++;
	}
	new[i] = exported_var(args->parsed_arg);
	new[i + 1] = 0;
	free_env(env, 0);
	return (new);
}

static int	cmd_is_valid(char *str, int i, t_args *args)
{
	if (args->is_command == 4)
		return (0);
	if (ft_isalpha(str[0]) == 0)
	{
		printf("export: `%s': not a valid identifier\n", str);
		return (1);
	}
	while (str[i])
	{
		if (str[i] == '=' && i != 0 && ft_isalpha(str[i]) == 0)
			return (0);
		i++;
	}
	printf("export: `%s': not a valid identifier\n", str);
	builtin_export(g_env, ft_export(1, "export"));
	return (1);
}

void	builtin_export(char **env, t_args *args)
{
	int		i;
	t_args	*head;

	head = args;
	if (args->next == NULL || args->next->to_use == 0
		|| args->next->is_separator == 1)
	{
		export_no_arg(env, 0, 0);
		return ;
	}
	while (args->next != NULL && args->next->to_use == 1
		&& args->next->is_separator != 1)
	{
		args = args->next;
		i = existing_var(g_env, args);
		if (args->to_use == 1 && i != 2)
		{
			i = cmd_is_valid(args->parsed_arg, 0, args);
			if (i != 1)
				g_env = copy_env(g_env, args, 0, 0);
		}
	}
	if (head->to_use == 4)
		free_list(head);
}
