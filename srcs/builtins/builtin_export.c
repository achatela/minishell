#include "minishell.h"

static int	env_lines(char **env)
{
	int	i;
	
	i = 0;
	while (env[i] != 0)
		i++;
	return (i + 1);
}

static char	**copy_env(char **env, char **new, int i, int j)
{
	while (env[i] != 0)
	{
		j = 0;
		new[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!new)
			return (NULL);
		while (env[i][j])
		{
			new[i][j] = env[i][j];
			j++;
		}
		new[i][j] = '\0';
		i++;
	}
	new[i] = malloc(sizeof(char));
	new[i] = 0;
	return (NULL);
}

void	builtin_export(char **env, int i)
{
	char	**new;

	(void)i;
	new = malloc(sizeof(char *) * env_lines(env) + 1);
	new = copy_env(env, new, 0, 0);
/*	while (env[i] != 0)
	{
		free(env[i]);
		i++;
	}
	free(env[i]);
	free(env);*/
	env = new;
}
