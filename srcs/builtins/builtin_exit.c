/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:24:05 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/13 14:53:59 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_max(t_args *args)
{
	if (ft_strlen(args->parsed_arg) > 20)
		return (1);
	if (args->parsed_arg[0] == '-')
	{
		if (ft_atoll(args->parsed_arg) > 0)
			return (1);
	}
	else
	{
		if (ft_atoll(args->parsed_arg) < 0)
			return (1);
	}
	return (0);
}	

void	exit_return(t_args *args, long long i)
{
	i = ft_atoi(args->parsed_arg) % 256;
	free_env(g_env, 0);
	exit(i);
}

void	check_args(t_args *args)
{
	if (args == NULL)
	{
		free_env(g_env, 0);
		exit(0);
	}
	else if (ft_strisnum(args->parsed_arg) == 1
		&& args->next != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		builtin_export(g_env, ft_export(1, "export"));
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
		builtin_export(g_env, ft_export(1, "export"));
	}
}

void	builtin_exit(t_args *args)
{
	long long	i;

	i = 0;
	args = args->next;
	check_args(args);
	if (check_max(args) == 1)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			args->parsed_arg);
		exit(2);
	}
	else if (args && ft_strisnum(args->parsed_arg) == 0)
		exit_return(args, i);
	return ;
}
