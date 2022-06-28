/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:39:02 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/08 16:36:49 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_access(t_args *sep, t_args *args)
{
	if (ft_strcmp(sep->parsed_arg, ">>") == 0)
		open(args->parsed_arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (ft_strcmp(sep->parsed_arg, ">") == 0)
		open(args->parsed_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
	{
		if (access(args->parsed_arg, R_OK) == -1)
		{
			printf("%s: No such file", args->parsed_arg);
			printf(" or directory\n");
			return (-1);
		}
	}
	return (0);
}

static void	first_redir_out(t_args *args, int i)
{
	while (args && args->is_separator != 2)
	{
		if (args && args->is_separator == 1)
			i = try_access(args, args->next);
		if (i == -1)
			return ;
		else
			args = args->next;
	}
}

static int	has_only_out(t_args *args)
{
	while (args && args->is_separator != 2)
	{
		if (args->is_separator == 1)
		{
			if (args->parsed_arg[0] != '<')
				return (0);
			args = args->next;
		}
		else
			args = args->next;
	}
	return (1);
}

int	redir_in(t_args *args, t_args *head, char **cmds)
{
	(void)head;
	if (ft_strcmp(args->parsed_arg, "<") == 0)
		return (first_redir_out(args, 0), 0);
	else if (has_only_out(args) == 1)
		return (only_out(args, args, cmds), 0);
	else
		return (out_in(args, args, cmds), 0);
}
