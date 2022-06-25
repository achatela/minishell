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

static int	has_redir(t_args *args)
{
	while (args)
	{
		if (args->parsed_arg[0] == '>' && args->is_separator == 1)
			return (1);
		args = args->next;
	}
	return (0);
}

static char	*get_file_name(t_args *args)
{
	while (args && args->parsed_arg[0] != '<' && args->is_separator != 1)
		args = args->next;
	if (args)
		args = args->next;
	return (args->parsed_arg);
}

static void	not_existing(t_args *args)
{
	int	fd;

	while (args && args->parsed_arg[0] != '<')
	{
		while (args && args->is_separator == 1)
		{
			args = args->next;
		}
		while (args && args->is_separator == 0)
			args = args->next;
		if (args && args->next)
		{
			if (args->parsed_arg[0] == '<')
				break ;
			args = args->next;
		}
		if (args && args->parsed_arg)
		{
			fd = open(args->parsed_arg, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			close(fd);
		}
	}
}

int	redir_in(t_args *args, t_args *head, char **cmds)
{
	char	*tmp;
	int		fd;

	fd = 0;
	if (has_redir(args) == 1)
	{
		tmp = get_file_name(args);
		//if (ft_check_access(tmp, 0) != 0)
		//	return (not_existing(head), 2);
		return (1);
	}
	else
		in_redir(args, head, cmds, fd);
	return (1);
}
