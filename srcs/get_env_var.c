#include "minishell.h"

static char	*cut_var_end(char *str, int i, int j)
{
	int		k;
	char	*ret;

	if (str[i] == '\0')
		i--;
	k = i;
	while (str[++i])
		j++;
	ret = malloc(sizeof(char) * j + 1);
	j = 0;
	while (str[++k])
	{
		ret[j] = str[k];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*get_env_var(char **env, char *var, int i)
{
	if (var == NULL)
		return (NULL);
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (cut_var_end(env[i], ft_strlen(var), 0));
		i++;
	}
	return (NULL);
}
