/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:41:46 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/13 16:18:52 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int sig, siginfo_t *info, void *null)
{
	(void)null;
	if (sig == SIGINT && info != NULL)
		kill(info->si_pid, SIGSTOP);
	if (sig == SIGQUIT)
	{
		kill(info->si_pid, SIGSTOP);
		return ;
	}
	return ;
}

void	handler(int sig, siginfo_t *info, void *null)
{
	if (sig == SIGQUIT && info->si_pid != 0)
		printf("\b\b  \b\b");
	if (sig == SIGQUIT && info->si_pid == 0)
	{
		builtin_export(g_env, ft_export(131, "export"));
		printf("Quit (core dumped)\n");
	}
	else if (sig == SIGINT && info->si_pid != 0)
	{
		printf("\n");
	//	rl_on_new_line();
	//	rl_replace_line("", 0);
	//	rl_redisplay();
	}
	else if (sig == SIGINT && info->si_pid == 0)
	{
		builtin_export(g_env, ft_export(130, "export"));
		printf("\n");
	}
	(void)null;
}
