/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:31:29 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/17 14:21:43 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env = NULL;

static char	*get_shlvl(char *str, int i, char *to_free)
{
	int		sh_lvl;
	char	*ret;
	char	*tmp;

	sh_lvl = ft_atoi(str + i) + 1;
	free(to_free);
	tmp = ft_itoa(sh_lvl);
	if (!tmp)
		return (NULL);
	ret = malloc(sizeof(char) * 7);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < 6)
		ret[i] = str[i];
	ret[i] = '\0';
	ret = ft_strjoin(ret, tmp);
	free(tmp);
	return (ret);
}

static char	**init_env(char **env, int i, int k)
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
		if (ft_strlen(env[i]) > 6)
			tmp = is_shlvl(env[i]);
		if (tmp == 1)
			g_env[i] = get_shlvl(env[i], 6, g_env[i]);
		else
		{	
			free(g_env[i]);
			g_env[i] = ft_strdup(env[i]);
		}
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

static void	while_main(int argc, t_echo *echo)
{
	char	*cmd;
	char	*prompt;

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
	free(prompt);
	free(cmd);
}

int	main(int argc, char **argv, char **env)
{
	t_echo				*echo;
	struct sigaction	act;

	argc = -1;
	(void)argv;
	echo = malloc(sizeof(t_echo));
	echo->print = 0;
	g_env = init_env(env, 0, 0);
	builtin_export(g_env, ft_export(0, "export"));
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	while (1)
		while_main(argc, echo);
	clear_history();
	free(echo);
	free_env(g_env, 0);
	return (0);
}
