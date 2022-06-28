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

void	only_out(t_args *args, t_args *head, char **cmds)
{
	char	*tmp;
	int		old_fd;
	int		fd;

	while (args && args->is_separator != 2)
	{
		if (args && args->is_separator == 1)
		{
			tmp = args->next->parsed_arg;
			if (try_access(args, args->next) == -1)
				return ;
			else
				args = args->next;
		}
		else
			args = args->next;
	}
	old_fd = dup(0);
	close(0);
	fd = open(tmp, O_RDONLY);
	send_builtin(head, cmds);
	close(fd);
	dup(old_fd);
	close(old_fd);
}

t_in_out	*init_in_out(void)
{
	t_in_out	*ret;

	ret = malloc(sizeof(t_in_out));
	ret->old_in = dup(0);
	ret->old_out = dup(1);
	ret->in = 0;
	ret->out = 0;
	return (ret);
}

int	open_in_out(t_args *sep, t_args *args, t_in_out *fds)
{
	if (ft_strcmp(sep->parsed_arg, "<") == 0)
	{
		fds->in = 1;
		close(0);
		fds->fd_in = open(args->parsed_arg, O_RDONLY);
	}
	else if ((ft_strcmp(sep->parsed_arg, ">") == 0
			|| ft_strcmp(sep->parsed_arg, ">>") == 0))
	{
		fds->out = 1;
		close(1);
		if (ft_strcmp(sep->parsed_arg, ">>") == 0)
			fds->fd_out = open(args->parsed_arg, O_WRONLY
					| O_APPEND | O_CREAT, 0644);
		else
			fds->fd_out = open(args->parsed_arg, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
	}
	return (0);
}

static void	reset_fd(t_in_out *fds)
{
	close(0);
	close(1);
	dup(fds->old_in);
	dup(fds->old_out);
	close(fds->old_in);
	close(fds->old_out);
	free(fds);
}

void	out_in(t_args *args, t_args *head, char **cmds)
{
	t_in_out	*fds;

	fds = init_in_out();
	while (args && args->is_separator != 2)
	{
		if (args && args->is_separator == 1)
		{
			if (try_access(args, args->next) == -1)
			{
				free(fds);
				return ;
			}
			open_in_out(args, args->next, fds);
			args = args->next;
		}
		else
			args = args->next;
	}
	send_builtin(head, cmds);
	reset_fd(fds);
}
