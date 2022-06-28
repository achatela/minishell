/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:30 by achatela          #+#    #+#             */
/*   Updated: 2022/06/22 17:27:23 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_and_wait(t_fd *pips)
{
	int	j;

	j = 0;
	dup2(pips->tmpin, 0);
	dup2(pips->tmpout, 1);
	close(pips->tmpin);
	close(pips->tmpout);
	close(pips->p[0]);
	close(pips->p[1]);
	while (j < 400)
	{
		j++;
		wait(NULL);
	}
}

void	pip2(t_pipe *pipes, t_args *head, t_fd *pips)
{
	(void)head;
	if (pips->pid == 0)
	{
		close(pips->p[0]);
		close(pips->p[1]);
		send_builtin(pipes->args, pipes->cmds);
		exit(1);
	}
	else
	{
		send_to_sep(pipes->args, pipes->args, pipes->cmds);
		while (pipes->args && pipes->args->is_separator != 2)
			pipes->args = pipes->args->next;
		if (pipes->args)
			pipes->args = pipes->args->next;
	}
}

int	pip(t_pipe *pipes, t_fd *pips)
{
	t_args	*head;

	pips->fdin = dup(pips->tmpin);
	while (pipes->args)
	{
		dup2(pips->fdin, STDIN_FILENO);
		close(pips->fdin);
		if (has_pip(pipes->args) == 0)
			pips->fdout = dup(pips->tmpout);
		else
		{
			pipe(pips->p);
			pips->fdout = pips->p[1];
			pips->fdin = pips->p[0];
		}
		dup2(pips->fdout, STDOUT_FILENO);
		close(pips->fdout);
		pips->pid = fork();
		pip2(pipes, head, pips);
		head = pipes->args;
	}
	close_and_wait(pips);
	return (1);
}
