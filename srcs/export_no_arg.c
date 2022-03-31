#include "minishell.h"

static void	sort_env(char **env, int i, int j)
{
	char	**new;
	char	*tmp;

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
	new[i] = malloc(sizeof(char));
	new[i] = 0;
	j = 0;
	i = 0;
	while (j < 1000000 && new[i + 1] != 0)
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
	while (new[i + 1] != 0)
	{
		//quand norme >> mettre begin/end dans des *char et free à chaque while
		printf("declare -x %s\"%s\"\n", cut_var_begin(new[i], 0, 0), cut_var_end(new[i], 0, 0));
		i++;
	}
}

void	export_no_arg(char **env, int j, int k)
{
	(void)j;
	(void)k;
	sort_env(env, 0, 0);
}
