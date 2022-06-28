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

static int	try_access(t_args *sep, t_args *args)
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

static void	only_out(t_args *args, t_args *head, char **cmds)
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

static t_in_out	*init_in_out(void)
{
	t_in_out	*ret;

	ret = malloc(sizeof(t_in_out));
	ret->old_in = dup(0);
	ret->old_out = dup(1);
	ret->in = 0;
	ret->out = 0;
	return (ret);
}

static int	open_in_out(t_args *sep, t_args *args, t_in_out *fds)
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

static void	out_in(t_args *args, t_args *head, char **cmds)
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
	close(0);
	close(1);
	dup(fds->old_in);
	dup(fds->old_out);
	close(fds->old_in);
	close(fds->old_out);
	free(fds);
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
