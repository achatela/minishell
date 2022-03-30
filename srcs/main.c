#include "minishell.h"

static char **g_env;

int	main(int argc, char **argv, char **env)
{
	char	**path;
	char	*cmd;

	(void)argc;
	(void)argv;
	g_env = env;
	path = get_path(g_env, 0);
	printf("%s\n", get_env_var(g_env, "HOME", 0));
	while (1 && path != NULL)
	{
		cmd = readline("minishell$>");
		add_history(cmd);
		if (cmd != NULL)
			parsing(cmd);
	}
	return (0);
}
