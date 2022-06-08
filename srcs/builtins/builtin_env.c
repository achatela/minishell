/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:23:30 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/08 17:48:25 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(int i, t_args *args)
{
	int	j;

	if (args->next && args->next->is_separator == 0)
	{
		printf("env: ‘%s’:", args->next->parsed_arg);
		printf(" No such file or directory\n");
		builtin_export(g_env, ft_export(127, "export"));
		return ;
	}
	while (g_env[i] != 0)
	{
		j = -1;
		while (g_env[i][++j])
		{
			if (g_env[i][j] == '=')
			{
				printf("%s\n", g_env[i]);
				break ;
			}
		}
		i++;
	}
	builtin_export(g_env, ft_export(0, "export"));
	return ;
}
