#include "minishell.h"

static int	env_is_path(char **env, int i)
{
	if (env[i][0] == 'P' && env[i][1] == 'A'
		&& env[i][2] == 'T' && env[i][3] == 'H'
		&& env[i][4] == '=')
		return (1);
	else
		return (0);
}

char	**get_path(char **env, int i)
{
	char	**ret;

	while (env[i] != 0)
	{
		if (env_is_path(env, i) == 0)
			i++;
		else
			break;
	}
	return(ft_split(env[i], ':'));
}
