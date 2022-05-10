/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:31:29 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/10 18:14:52 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env = NULL;

static int	is_shlvl(char *str)
{
	if (str[0] == 'S' && str[1] == 'H' && str[2] == 'L'
		&& str[3] == 'V' && str[4] == 'L' && str[5] == '=')
		return (1);
	return (0);
}

static char	**init_env(char **env, int i, int j, int k)
{
	int	tmp;

	while (env[k] != 0)
		k++;
	g_env = malloc(sizeof(char *) * env_lines(env));
	if (!g_env)
		return (NULL);
	while (i < k)
	{
		g_env[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!g_env[i])
			return (NULL);
		j = 0;
		if (ft_strlen(env[i]) > 6)
			tmp = is_shlvl(env[i]);
		while (env[i][j])
		{
			if (tmp == 1 && j == 6)
				g_env[i][j] = env[i][j] + 1;
			else
				g_env[i][j] = env[i][j];
			j++;
		}
		g_env[i][j] = '\0';
		i++;
	}
	g_env[i] = 0;
	return (g_env);
}

static char	*set_cmd(char *cmd, char *exit)
{
	int	i;

	i = -1;
	cmd = malloc(sizeof(char) * 5);
	while (exit[++i])
		cmd[i] = exit[i];
	cmd[i] = '\0';
	return (cmd);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	char	*prompt;
	int		i;
	t_echo	*echo;
	struct sigaction	act;

	i = 4;
	argc = -1;
	(void)argv;
	echo = malloc(sizeof(t_echo));
	echo->print = 0;
	g_env = init_env(env, 0, 0, 0);
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	while (--i < 10)
	{
		prompt = get_prompt(argc);
		cmd = readline(prompt);
		if (cmd == NULL)
		{
			cmd = set_cmd(cmd, "exit");
			printf("exit\n");
		}
		if (cmd[0] != '\0')
		{
			add_history(cmd);
			parsing(cmd, echo);
		}
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		free(prompt);
		free(cmd);
	}
	clear_history();
	free(echo);
	free_env(g_env, 0);
	return (0);
}
