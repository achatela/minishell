#include "minishell.h"

static int	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f' || c == ' ')
		return (1);
	return (0);
}

static int	word_length(char *cmd, int i, int j)
{
	while (is_whitespace(cmd[i]) == 0 && cmd[i])
	{
		i++;
		j++;
	}
	return (j);
}

static char	*get_next_word(char *cmd, int i, int j)
{
	char	*tab;

	tab = malloc(sizeof(char) * (word_length(cmd, i, 0) + 1));
	while (is_whitespace(cmd[i]) == 0 && cmd[i])
	{
		tab[j] = cmd[i];
		i++;
		j++;
	}
	tab[j] = '\0';
	return (tab);
}

static int	not_ended(char *cmd, int i)
{
	while (cmd[i])
	{
		if (ft_isalpha(cmd[i]) == 1 && ft_isalnum(cmd[i]) == 1
			&& ft_isprint(cmd[i]) == 1)
			return (0);
		i++;
	}
	return (1);
}

char	**str_to_tabs(char *cmd, int i, int j)
{
	char	**ret;

	ret = malloc(sizeof(char *) * (arg_number(cmd, 0, 0) + 2));
	if (!ret)
		return (NULL);
	while (cmd[i] && not_ended(cmd, i) == 0 && j <= arg_number(cmd, 0, 0))
	{
		while (is_whitespace(cmd[i]) == 1 && cmd[i])
			i++;
		ret[j] = get_next_word(cmd, i, 0);
		while (is_whitespace(cmd[i]) == 0 && cmd[i])
			i++;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}
