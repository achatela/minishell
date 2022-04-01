#include "minishell.h"

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

	new = malloc(sizeof(char *) * (env_lines(g_env) + 1));
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
	free_env(env, 0);
	return (new);
}

static int	cmd_is_valid(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	builtin_export(char **env, char **cmds)
{
	char	*str;
	char	*tmp;

//	if (existing_var(env, cmds))
//		return ;
	if (cmds[1] == NULL)
	{
		export_no_arg(env, 0, 0);
		return ;
	}
	if (exisiting_var(g_env, cmds) == 2)
		return ;
/*	if (cmds[1] != NULL)
	{
		tmp = cut_var_begin(cmds[1], 0, 0);
		str = get_env_var(g_env, tmp, 0);
		free(tmp);
	}
	else
		return ;
	if (str != NULL)
		exisiting_var(env, cmds);
	free(str);*/
	(void)str;
	(void)tmp;
	if (cmds[1] != NULL)
	{
		if(cmd_is_valid(cmds[1], 0) == 1)
			return ;
	}
	g_env = copy_env(g_env, cmds, 0, 0);
}
