#include "minishell.h"

char	*search_env(char *str, int i, int j)
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
	ret[j] = '\0';
	return (ret);
}

int	check_name(char *str)
{
	int i;

	i = -1;
	if (!ft_isalpha(str[0]))
		return (1);
	while (str[++i])
	{
		if (ft_isalnum(str[i]) == 0)
			return (1);
	}
	return (0);
	
}

void    builtin_unset(char **env, char **cmds)
{
	int i;
	char *tmp;

	i= 1;
	if (!cmds[1])
		return ;
	while (env[++i])
	{
		tmp = search_env(env[i], 0, 0);
		if (check_name(cmds[1]) == 1)
			printf("bash: unset: `%s': not a valid identifier\n", cmds[1]);
		else if (ft_strcmp(tmp, cmds[1]) == 0)
		{
			tmp = 0;
			env[i] = tmp;
			free(tmp);
		}
		free(tmp);
	}
}