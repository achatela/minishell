#include "minishell.h"

char	**g_env = NULL;

static char	**init_env(char **env, int i, int j, int k)
{
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
		while (env[i][j])
		{
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
	int		i = 4;
	t_echo	*echo;

	argc = -1;
	(void)argv;
	echo = malloc(sizeof(t_echo));
	echo->print = 0;
	g_env = init_env(env, 0, 0, 0);
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	while (--i)
	{
		prompt = get_prompt(g_env, argc);
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
	clear_history();
	free(echo);
	free_env(g_env, 0);
	return (0);
}
