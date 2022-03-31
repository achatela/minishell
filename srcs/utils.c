#include "minishell.h"

char	*cut_var_begin(char *str, int i, int j)
{
	char	*ret;

	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	ret = malloc(sizeof(char) * i + 2);
	if (!ret)
		return (NULL);
	while (str[j] != '=')
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '=';
	ret[j + 1] = '\0';
	return (ret);
}

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
