/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:31:29 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/20 16:38:47 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env = NULL;

static void	while_main(int argc)
{
	char	*cmd;
	char	*prompt;

	prompt = get_prompt(argc);
	cmd = readline(prompt);
	if (cmd != NULL && spaces(cmd) == 1)
	{
		free(prompt);
		free(cmd);
		return ;
	}
	if (cmd == NULL)
		cmd = set_cmd(cmd, "exit");
	if (cmd[0] != '\0')
	{
		add_history(cmd);
		parsing(cmd);
	}
	free(prompt);
	free(cmd);
}

int	main(int argc, char **argv, char **env)
{
	struct sigaction	act;

	argc = -1;
	(void)argv;
	g_env = init_env(env, 0, 0);
	builtin_export(g_env, ft_export(0, "export"));
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	while (1)
		while_main(argc);
//	clear_history();
//	free_env(g_env, 0);
	return (0);
}
