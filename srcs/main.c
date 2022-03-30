#include "minishell.h"

char	**g_env = NULL;

int	main(int argc, char **argv, char **env)
{
	char	**path;
	char	*cmd;

	(void)argc;
	(void)argv;
	g_env = env;
	path = get_path(g_env, 0);
	while (1 && path != NULL)
	{
		cmd = readline(get_prompt(g_env, -1));
		add_history(cmd);
		if (cmd != NULL)
			parsing(cmd);
	}
	return (0);
}
