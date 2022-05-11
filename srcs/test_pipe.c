/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:30 by achatela          #+#    #+#             */
/*   Updated: 2022/05/11 14:15:42 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_sep(t_args *args)
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

int	pip(t_args *args, int start, int fd, int last, char **cmds)
{
	int		p[2];
	int		pid;
	int		ret;

	ret = 0;
	pipe(p);
	pid = fork();
	if (pid == 0)
	{
		if (start == 1 && last == 0 && fd == 0)
			dup2(p[1], 1);
		else if (start == 0 && last == 0 && fd != 0)
		{
			dup2(fd, 0);
			dup2(p[1], 1);
		}
		else
			dup2(fd, 0);
		if (has_sep(args) == 0)
			send_builtin(args, 0, cmds);
		ret = 1;
		exit(ret);
	}
	waitpid(pid, &ret, 0);
	close(p[1]);
	if (fd != 0)
		close(fd);
	if (last == 1)
		close(p[0]);
	return (p[0]);
}
