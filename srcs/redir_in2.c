/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:32:04 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/08 16:36:40 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	last_redir_in(t_args *args)
{
	while (args)
	{
		while (args && args->is_separator == 0)
			args = args->next;
		if (args && args->is_separator == 1)
		{
			if (args->parsed_arg[0] == '<' && args->parsed_arg[1] == '\0')
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

int	in_redir(t_args *args, t_args *head, char **cmds, int fd)
{
	while (args && last_redir_in(args) != 0
		&& args->next && args->next->is_separator != 2)
	{
		while (args && args->is_separator == 0)
			args = args->next;
		while (args && args->is_separator == 1)
			args = args->next;
		if (ft_check_access(args->parsed_arg, 0) != 0)
			return (3);
		get_fd(head, args, fd, cmds);
	}
	return (0);
}
