#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	**path;
	char	*cmd;

	(void)argc;
	(void)argv;
	path = get_path(env, 0);
	while (1 && path != NULL)
	{
		cmd = readline("minishell$>");
		add_history(cmd);
		if (cmd != NULL)
			parsing(cmd);
		getcwd(NULL, 0);
	}
	return (0);
}
