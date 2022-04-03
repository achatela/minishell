#include "minishell.h"

void	builtin_env(int i)
{
	while (g_env[i] != 0)
	{
		printf("%s\n", g_env[i]);
		i++;
	}
	return ;
}
