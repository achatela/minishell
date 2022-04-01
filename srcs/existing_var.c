#include "minishell.h"

static char	**remove_var(char **env, char *tmp, int i, int j)
{
	char	**new;
	int		k;

	new = malloc(sizeof(char *) * (env_lines(env) - 1));
	if (!new)
		return (NULL);
	while (env[++i] != 0)
	{
		k = -1;
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
			i++;
		else if (ft_strncmp(tmp, env[i], ft_strlen(tmp) != 0))
		{
			new[j] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
			while (env[i][++k])
				new[j][k] = env[i][k];
			new[j][k] = '\0';
			i++;
			j++;
		}
	}
	new[j] = 0;
	free_env(env, 0);
	return (new);
}

static int	exact_copy(char **env, char **cmds)
{
	int		i;

	i = 0;
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], cmds[1], (ft_strlen(env[i]))) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exisiting_var(char **env, char **cmds)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = cut_var_begin(cmds[1], 0, 0);
	if (!tmp)
		return (1);
	if (exact_copy(g_env, cmds) == 1)
	{
		free(tmp);
		return (2);
	}
	while (env[i] != 0)
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			g_env = remove_var(g_env, tmp, -1, 0);
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}
