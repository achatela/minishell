/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:23:30 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/20 14:39:04 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(int i, t_args *args)
{
	if (args->next && args->next->is_separator == 0)
	{
		printf("env: ‘%s’:", args->next->parsed_arg);
		printf(" No such file or directory\n");
		builtin_export(g_env, ft_export(127, "export"));
		return ;
	}
	while (g_env[i] != 0)
	{
		printf("%s\n", g_env[i]);
		i++;
	}
	builtin_export(g_env, ft_export(0, "export"));
	return ;
}
