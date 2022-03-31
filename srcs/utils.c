#include "minishell.h"

void	free_cmds(char **cmds, int i)
{
	while (cmds[i] != NULL)
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

int	env_lines(char **env)
{
	int	i;

	i = 0;
	while (env[i] != 0)
		i++;
	return (i + 1);
}

void	free_env(char **env, int i)
{
	while (env[i] != 0)
	{
		free(env[i]);
		i++;
	}
}
