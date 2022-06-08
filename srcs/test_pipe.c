/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:30 by achatela          #+#    #+#             */
/*   Updated: 2022/06/08 16:52:12 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_sep2(t_args *args)
{
	t_args	*head;

	head = args;
	while (head)
	{
		if (head && (head->is_separator == 1))
			return (1);
		head = head->next;
	}
	return (0);
}

static void	child_pip(int start, int last, int *p, t_pipe *pipes)
{
	if (start == 1 && last == 0 && pipes->fd == 0)
		dup2(p[1], 1);
	else if (start == 0 && last == 0 && pipes->fd != 0)
	{
		dup2(pipes->fd, 0);
		dup2(p[1], 1);
	}
	else
		dup2(pipes->fd, 0);
	if (has_sep2(pipes->args) == 0)
		send_builtin(pipes->args, pipes->cmds);
}

int	pip(t_pipe *pipes, int start, int fd, int last)
{
	int		p[2];
	int		pid;
	int		ret;

	ret = 0;
	pipe(p);
	pid = fork();
	pipes->fd = fd;
	if (pid == 0)
	{
		child_pip(start, last, p, pipes);
		ret = 1;
		exit(ret);
	}
	waitpid(pid, &ret, 0);
	close(p[1]);
	if (pipes->fd != 0)
		close(pipes->fd);
	if (last == 1)
		close(p[0]);
	return (p[0]);
}
