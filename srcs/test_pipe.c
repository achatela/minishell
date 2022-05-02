/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:44:47 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/02 16:44:48 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		send_builtin(args, 0, cmds);
	//	redir(args, cmds);
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
