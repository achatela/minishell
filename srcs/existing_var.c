#include "minishell.h"

static int	exact_copy(char **env, t_args *args)
{
	int		i;
	int		length;

	(void)env;
	i = 0;
	while (g_env[i] != 0)
	{
		length = ft_strlen(g_env[i]);
		if (ft_strlen(args->parsed_arg) > length)
				length = ft_strlen(args->parsed_arg);
		if (ft_strncmp(g_env[i], args->parsed_arg, length) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	existing_var(char **env, t_args *args)
{
	char	*tmp;
	int		i;

	i = 0;
	(void)env;
	tmp = cut_var_begin(args->parsed_arg, 0, 0);
	if (!tmp)
		return (1);
	if (exact_copy(g_env, args) == 1)
	{
		free(tmp);
		return (2);
	}
	while (g_env[i] != 0)
	{
		if (ft_strncmp(tmp, g_env[i], ft_strlen(tmp)) == 0)
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
