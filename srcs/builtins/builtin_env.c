#include "minishell.h"

void	builtin_env(char **env, int i)
{
	while (env[i] != 0)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return ;
}
