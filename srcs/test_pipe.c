/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:30 by achatela          #+#    #+#             */
/*   Updated: 2022/06/17 15:50:03 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_signals(void)
{
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGSTOP, SIG_IGN);
	// signal(SIGINT, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
}

int	pip(t_pipe *pipes, int start, int fd, int last)
{
	int		p[2];
	int		pid;
	int		ret;
	int		tmpin = dup(0);
	int		tmpout = dup(1);
	int		fdin;
	int		fdout;
	t_args	*head;
	int		i = 0;

	(void)fd;
	(void)start;
	(void)ret;
	(void)last;
	ret = 0;
	fdin = dup(tmpin);
	while (pipes->args)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		if (has_pip(pipes->args) == 0)
			fdout = dup(tmpout);
		else
		{
			pipe(p);
			fdout = p[1];
			fdin = p[0];
		}
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		pid = fork();
		if (pid == 0)
		{
			close(p[0]);
			close(p[1]);
			exec_bin(pipes->cmds, pipes->args, 0);
			if (has_pip(pipes->args) == 0)
				kill(pid, SIGCHLD);
			ret = 1;
			exit(ret);
		}
		else
		{
			while (pipes->args && (pipes->args->is_separator == 0
				|| pipes->args->is_separator == 1) && i == 0)
				pipes->args = while_send_sep(pipes->args, &i, head, pipes->cmds);
			if (pipes->args && pipes->args->is_separator == 0)
				pipes->args = skip_cmd(pipes->args);
			while (pipes->args && pipes->args->is_separator == 2)
				pipes->args = pipes->args->next;
			i = 0;
		}
		head = pipes->args;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	close(p[0]);
	close(p[1]);
	return (1);
}
// /*	ret = 0;
// 	(void)fd;
// 	pipe(p);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		child_pip(start, last, p, pipes);
// 		exit(ret);
// 	}
// 	else if (pid != 0)
// 		waitpid(pid, &ret, 0);
// 	close(p[1]);
// 	if (pipes->fd != 0)
// 		close(pipes->fd);
// 	if (last == 1)
// 		close(p[0]);
// 	return (p[0]);*/
// }

// int	pip(t_pipe *pipes, int start, int fd, int last)
// {
// 	(void)start;
// 	(void)last;
// 	(void)fd;
// 	int	i = 0;
// 	t_args *head;
// 	int pfd[2];
// 	int pid;
// 	if (pipe(pfd) == -1)
// 		return (1);
	
// 	while (pipes->args)
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 		return 2;
// 		if (pid == 0)
// 		{
// 			dup2(pfd[1], 1);
// 			close(pfd[0]);
// 			close(pfd[1]);
// 			exec_bin(pipes->cmds, pipes->args, 0);
// 		}
// 		else
// 		{
// 			while (pipes->args && (pipes->args->is_separator == 0
// 				|| pipes->args->is_separator == 1) && i == 0)
// 				pipes->args = while_send_sep(pipes->args, &i, head, pipes->cmds);
// 			if (pipes->args && pipes->args->is_separator == 0)
// 				pipes->args = skip_cmd(pipes->args);
// 			while (pipes->args && pipes->args->is_separator == 2)
// 				pipes->args = pipes->args->next;
// 			i = 0;
// 		}
// 		head = pipes->args;
// 	}
// 	close(pfd[0]);
// 	close(pfd[1]);
// 	waitpid(pid, NULL, 0);
// 	return (0);
// }