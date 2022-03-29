#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	**path;
	char	*cmd;

	(void)argc;
	(void)argv;
	path = get_path(env, 0);
	while (1)
	{
		cmd = readline("minishell$>");
		if (cmd != NULL)
			parsing(cmd);
	}
	return (0);
}
