/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:41:46 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/09 13:34:42 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig, siginfo_t *info, void *null)
{
	(void)null;
	if (sig == SIGINT && info->si_pid == 0)
	{
		printf("\n");
		kill(info->si_pid, SIGQUIT);
	}
	if (sig == SIGINT && info->si_pid != 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		printf("\b\b  \b\b");
}
