/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:41:46 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/14 18:30:35 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int sig, siginfo_t *info, void *null)
{
	(void)null;
	if (sig == SIGINT)
		kill(info->si_pid, SIGSTOP);
	return ;
}

void	handler(int sig, siginfo_t *info, void *null)
{
	if (sig == SIGQUIT)
		printf("\b\b  \b\b");
	else if (sig == SIGINT && info->si_pid != 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		builtin_export(g_env, ft_export(130, "export"));
	}
	else if (sig == SIGINT && info->si_pid == 0)
		printf("\n");
	(void)null;
}
