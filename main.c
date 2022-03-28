#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	**path;
	int	i;

	i = 0;
	path = get_path(env, 0);
	while (path[i] != 0)
	{
		printf("%s\n", path[i]);
		i++;
	}
	return (0);
}
