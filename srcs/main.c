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

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	char	*prompt;
	int		i = 40;
	t_echo	*echo;

	argc = -1;
	(void)argc;
	(void)argv;
	echo = malloc(sizeof(t_echo));
	echo->print = 0;
	g_env = init_env(env, 0, 0, 0);
	while (--i)
	{
		prompt = get_prompt(g_env, -1);
		cmd = readline(prompt);
		if (cmd[0] != '\0')
		{
			add_history(cmd);
			parsing(cmd, echo);
		}
		free(prompt);
		free(cmd);
	}
	clear_history();
	free_env(g_env, 0);
	return (0);
}
