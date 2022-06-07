/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:24:05 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/07 17:01:10 by cjimenez         ###   ########.fr       */
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

int	check_args(int nb, t_args *args)
{
	if (ft_strisnum(args->parsed_arg) == 1 || check_max(args) == 1)
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			args->parsed_arg);
		exit(2);
	}
	else if (nb > 1)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		builtin_export(g_env, ft_export(1, "export"));
		return (1);
	}
	return (0);
}

void	builtin_exit(t_args *args)
{
	long long	i;
	int			nb;
	t_args		*tmp;

	i = 0;
	nb = 0;
	tmp = args;
	args = args->next;
	if (args == NULL)
	{
		printf("exit\n");
		exit (0);
	}
	while (tmp->next != NULL)
	{
		nb++;
		tmp = tmp->next;
	}
	if (check_args(nb, args) == 0)
		exit_return(args, i);
}
