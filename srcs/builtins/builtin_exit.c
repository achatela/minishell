/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:24:05 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/02 14:27:15 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_null(t_args *args)
{
	if (args == NULL)
	{
		free_env(g_env, 0);
		exit(0);
	}
}

int	builtin_exit(t_args *args)
{
	int	i;

	i = 0;
	args = args->next;
	check_null(args);
	if (ft_strisnum(args->parsed_arg) == 1
		&& args->next != NULL)
		printf("minishell: exit: too many arguments\n");
	else if (ft_strisnum(args->parsed_arg) == 1)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			args->parsed_arg);
		printf("[%s]\n", args->parsed_arg);
		exit(2);
	}
	else if (args && args->next)
	{
		printf("minishell: exit: too many arguments\n");
		exit(2);
	}
	else if (args && ft_strisnum(args->parsed_arg) == 0)
	{
		i = ft_atoi(args->parsed_arg) % 256;
		free_env(g_env, 0);
		exit(i);
	}
	return (0);
}
