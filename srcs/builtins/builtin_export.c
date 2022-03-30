#include "minishell.h"

static int	env_lines(char **env)
{
	int	i;
	
	i = 0;
	while (env[i] != 0)
		i++;
	return (i + 1);
}

static char	*exported_var(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!ret)
		return (NULL);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static char	**copy_env(char **env, char **cmds, int i, int j)
{
	char	**new;

	new = malloc(sizeof(char *) * (env_lines(env) + 1));
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
	new[i] = exported_var(cmds[1]);
	new[i + 1] = malloc(sizeof(char));
	new[i + 1] = 0;
	return (new);
}

void	builtin_export(char **env, char **cmds, int i)
{
	if (cmds[1] == NULL)
	{
//		export_no_arg();
		return ;
	}
	g_env = copy_env(env, cmds, 0, 0);
	while (env[i] != 0)
	{
		free(env[i]);
		i++;
	}
}
