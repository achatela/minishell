#include "minishell.h"

static int	env_is_sorted(char **env, int i)
{
	while (env[i] != 0)
	{
		if(ft_strcmp(env[i], env[i + 1]) < 0)
			return (1);
		i++;
	}
	return (0);
}

static void	sort_env(char **env, int i, int j)
{
	char	**new;
	char	*tmp;
	char	*tmp2;

	new = malloc(sizeof(char *) * (env_lines(env)));
	while (env[i] != 0)
	{
		j = 0;
		new[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!new)
			return ;	
		while (env[i][j])
		{
			new[i][j] = env[i][j];
			j++;
		}
		new[i][j] = '\0';
		i++;
	}
	new[i] = 0;
	j = 0;
	i = 0;
	while (env_is_sorted(env, 0) != 0 && new[i + 1] != 0)
	{
		if (ft_strcmp(new[i], new[i + 1]) > 0)
		{
			tmp = new[i];
			new[i] = new[i + 1];
			new[i + 1] = tmp;
			i = -1;
		}
		i++;
		j++;
	}
	i = 0;
	while (new[i] != 0)
	{
		tmp = cut_var_begin(new[i], 0, 0);
		tmp2 = cut_var_end(new[i], 0, 0);
		if (tmp[0] != '_')
			printf("declare -x %s\"%s\"\n", tmp, tmp2);
		free(tmp);
		free(tmp2);
		i++;
	}
	free_env(new, 0);
}

void	export_no_arg(char **env, int j, int k)
{
	(void)j;
	(void)k;
	sort_env(env, 0, 0);
}
