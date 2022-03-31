#include "minishell.h"

static char	*cut_var(char *str, int i, int j)
{
	int		k;
	char	*ret;

	k = i;
	while (str[++i] != '\0')
		j++;
	ret = malloc(sizeof(char) * j + 1);
	j = 0;
	while (str[++k] != '\0')
	{
		ret[j] = str[k];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*get_env_var(char **env, char *var, int i)
{
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (cut_var(env[i], ft_strlen(var), 0));
		i++;
	}
	return (NULL);
}
