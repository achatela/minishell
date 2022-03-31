#include "minishell.h"

char	**g_env = NULL;

static char	**init_env(char **env, int i, int j, int k)
{
	while (env[k] != 0)
		k++;
	g_env = malloc(sizeof(char *) * (k + 1));
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
	char	**cmds;
	char	*cmd;

	argc = -1;
	(void)argc;
	(void)argv;
	g_env = init_env(env, 0, 0, 0);
//	path = get_path(g_env, 0);	/*à deplacer plus tard*/
	while (1)
	{
		cmd = readline(get_prompt(g_env, -1));
		add_history(cmd);
		if (cmd != NULL)
			cmds = parsing(cmd);
		if (cmds)
		free_cmds(cmds, 0);
	}
	while (g_env[++argc] != 0)
		free(g_env[argc]);
	free(g_env);
	return (0);
}
