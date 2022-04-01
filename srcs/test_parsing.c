#include "minishell.h"

static int	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f' || c == ' ')
		return (1);
	return (0);
}

/*static int	get_next_quote(char *str, int i)
{
	char	tmp;

	tmp = str[i];
	while (str[++i])
	{
		if (str[i] == tmp || str[i] == tmp)
		{
			printf("in next quote = str[%d] = %c\n", i, str[i]);
			return (i);
		}
	}
	return (-1);
}*/

static int	arg_number2(char *cmd, int i, int j, int k)
{
	if (cmd[i] != ' ' && ft_isprint(cmd[i]) == 1)
		k++;
	while (cmd[i] && is_whitespace(cmd[i]) == 1)
		i++;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == 39)
		{
			j = i;
			i++;
			while (cmd[i] && cmd[i] != cmd[j])
				i++;
			if (cmd[i] == '\0')
				return (-1);
			else if (cmd[i] == '\0')
				return (k);
			if (j >= 1 && ft_isprint(cmd[j + 1]) == 0)
				k++;
			i++;
		}
		else if (is_whitespace(cmd[i]) == 1)
		{
			if (cmd[i + 1] != ' ' && ft_isprint(cmd[i + 1]) == 1)
				k++;
			i++;
		}
		else if (cmd[i + 1] != ' ' && ft_isprint(cmd[i + 1] == 1))
			i++;
		else
			i++;
	}
	return (k);
}

char	**new_parsing(char *cmd, int i, int j)
{
	char	**cmds;
	
	(void)i;
	(void)j;
	cmds = malloc(sizeof(char *) * (arg_number2(cmd, 0, 0, 0) + 1));
	if (!cmds)
		return (NULL);
	return (cmds);
}
