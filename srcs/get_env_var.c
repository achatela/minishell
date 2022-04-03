#include "minishell.h"

char	*cut_var_end(char *str, int i, int j)
{
	int		k;
	char	*ret;

	while (str[i] != '=')
		i++;
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
	(void)env;
	if (var == NULL)
		return (NULL);
	while (g_env[i] != 0)
	{
		if (ft_strncmp(g_env[i], var, ft_strlen(var)) == 0)
			return (cut_var_end(g_env[i], 0, 0));
		i++;
	}
	i = 0;
	return (NULL);
}
