/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:24:05 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/06 16:11:25 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_null(t_args *args)
{
	if (args == NULL)
	{
		free_env(g_env, 0);
		exit(0);
	}
}

void	exit_return(t_args *args, int i)
{
	i = ft_atoi(args->parsed_arg) % 256;
	free_env(g_env, 0);
	exit(i);
}

void	builtin_exit(t_args *args)
{
	int	i;

	i = 0;
	args = args->next;
	check_null(args);
	if (ft_strisnum(args->parsed_arg) == 1
		&& args->next != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		args->echo->print = 1;
	}
	else if (ft_strisnum(args->parsed_arg) == 1)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			args->parsed_arg);
		exit(2);
	}
	else if (args && args->next)
	{
		printf("minishell: exit: too many arguments\n");
		args->echo->print = 1;
	}
	else if (args && ft_strisnum(args->parsed_arg) == 0)
		exit_return(args, i);
}
