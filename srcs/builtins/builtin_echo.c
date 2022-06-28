/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:21:23 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/30 14:13:13 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i++] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

static void	print_n(t_args *args)
{
	args = args->next;
	while (args && is_n(args->parsed_arg) == 1)
		args = args->next;
	while (args && args->to_use == 1
		&& args->is_separator == 0)
	{
		printf("%s", args->parsed_arg);
		args = args->next;
		if (args != NULL && args->is_separator == 0)
			printf(" ");
	}
}

static int	check_n(t_args *args, int i)
{
	if (args->next->parsed_arg[0] == '-'
		&& args->next->parsed_arg[1] == 'n')
	{
		while (args->next->parsed_arg[++i])
		{
			if (args->next->parsed_arg[i] != 'n')
			{
				args = args->next;
				while (args && args->to_use == 1 && args->is_separator == 0)
				{
					i = -1;
					while (args->parsed_arg[++i])
						printf("%c", args->parsed_arg[i]);
					if (!(args->next && args->next->is_separator != 0))
						printf(" ");
					args = args->next;
				}
				builtin_export(g_env, ft_export(0, "export"));
				return (printf("\n"), 1);
			}
		}
		print_n(args);
		return (1);
	}
	return (0);
}

int	builtin_echo(t_args *args, int i)
{
	if (args->next != NULL && ft_strlen(args->next->parsed_arg) > 1)
	{
		if (check_n(args, 1) == 1)
			return (1);
	}
	args = args->next;
	while (args && args->to_use == 1 && args->is_separator == 0)
	{
		i = -1;
		while (args->parsed_arg[++i])
			printf("%c", args->parsed_arg[i]);
		if (!(args->next && args->next->is_separator != 0))
			printf(" ");
		args = args->next;
	}
	builtin_export(g_env, ft_export(0, "export"));
	printf("\n");
	return (1);
}
