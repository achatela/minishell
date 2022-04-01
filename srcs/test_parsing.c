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

char	**new_parsing(char *cmd, int i, int j, int k)
{
	char	**cmds;
	int		l;
	
	l = 0;
	if (arg_number2(cmd, 0, 0, 0) == -1)
		return (printf("Quotes non fermées\n"), NULL);
	cmds = malloc(sizeof(char *) * (arg_number2(cmd, 0, 0, 0) + 1));
	if (!cmds)
		return (NULL);
	while (cmd[i] && is_whitespace(cmd[i]) == 1)
		i++;
	i++;
	while (cmd[i])
	{
		k = i;
		while (cmd[i] != ' ')
		{
			while (cmd[i] && cmd[i + 1] != ' ')
			{
				i++;
				if (cmd[i] == '"' || cmd[i] == 39)
				{
					j = i;
					i++;
					while (cmd[i] && cmd[i] != cmd[j])
					{
						i++;
						if (cmd[i + 1] == cmd[j] && (cmd[i + 2] == '"' || cmd[i + 2] == 39))
						{
							j = i + 2;
							i += 3;
						}
					}
				}
				cmds[l] = malloc(sizeof(char) * (i - k));
				if (!cmds[l])
					return (NULL);
				j = k;
				k = 0;
				while (j != i)
				{
					if (cmd[j] != '"' && cmd[j] != 39)
					{
						cmds[l][k] = cmd[j];
						k++;
					}
					j++;
				}
				cmds[l][k] = '\0';
				i++;
				l++;
			}
		}
	}
	cmds[l] = malloc(sizeof(char));
	cmds[l] = 0;
	i = 0;
	printf("ici\n");
	while (cmds[i] != 0)
	{
		printf("%s\n", cmds[i]);
		i++;
	}
	return (cmds);
}


/*char	**new_parsing(char *cmd, int i, int j, int k)
{
	char	**cmds;
	int		l;
	
	l = 0;
	if (arg_number2(cmd, 0, 0, 0) == -1)
		return (printf("Quotes non fermées\n"), NULL);
	cmds = malloc(sizeof(char *) * (arg_number2(cmd, 0, 0, 0) + 1));
	if (!cmds)
		return (NULL);
	while (cmd[i] && is_whitespace(cmd[i]) == 1)
		i++;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == 39)
		{
			j = i;
			k = i;
			i++;
			while (cmd[i] && cmd[i] != cmd[j])
			{
				i++;
				if (cmd[i + 1] == cmd[j] && (cmd[i + 2] == '"' || cmd[i + 2] == 39))
				{
					j = i + 2;
					i += 3;
				}
			}
			cmds[l] = malloc(sizeof(char) * (k - i));
			if (!cmds[l])
				return (NULL);
			j = k;
			k = 0;
			while (++j != i)
			{
				cmds[l][k] = cmd[j];
				k++;
			}
			cmds[l][k] = '\0';
			i++;
		}
	}
	return (cmds);
}*/
