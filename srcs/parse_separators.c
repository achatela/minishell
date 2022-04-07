#include "minishell.h"

static int	is_separator(char *str, int i)
{
	if ((str[i] == '|' && str[i + 1]) || i > 0 || (str[i] == '|' && i > 0 && str[i - 1]))
		return (1);
	else if ((str[i] == '<' && str[i + 1]) || (str[i] == '<' && i > 0 && str[i - 1]
			&& (str[i - 1] != '<' && str[i - 1] != '>')))
		return (1);
	else if ((str[i] == '>' && str[i + 1]) || (str[i] == '>' && i > 0 && str[i - 1]
			&& (str[i - 1] != '<' && str[i - 1] != '>')))
		return (1);
	else if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '>' && i > 0 && str[i - 1]))
		return (2);
	else if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '<' && i > 0 && str[i - 1]))
		return (2);
	return (0);
}

static int	count_args(char **cmds, int i, int j, int k)
{
	while (cmds[i] != 0)
	{
		j = 0;
	//	if (is_separator(cmds[i], j) != 0)
	//	{
	//		printf("is separator = 0 begin\n");
	//		k++;
	//		j++;
	//	}
		while (cmds[i][j] != '\0')
		{
		//	while ((j != 0 && cmds[i][j - 1]) || cmds[i][j])
		//	{
				printf("e%ce\n", cmds[i][j]);
				if (is_separator(cmds[i], j) == 2)
				{
					printf("is separator = 2\n");
					j += 2;
					k++;
				}
				else if (is_separator(cmds[i], j) == 1)
				{
					printf("is separator = 1\n");
					j++;
					k++;
				}
				else
				{
					printf("is separator = 0 end\n");
					j++;
				}
		//	}
		}
		i++;
	}
	printf("k = %d\n", k);
	return (k);
}

static char **new_cmds(char **cmds, int i, int j, int k)
{
	(void)i;	
	(void)j;	
	(void)k;	
	return(cmds);
}

char	**parse_separators(char **cmds, int i)
{
	int	j;

	j = 0;
	while (cmds[i] != 0)
	{
		printf("cmds[%d] = %s\n", i, cmds[i]);
		i++;
	}
	j = count_args(cmds, 0, 0, 0);
	if (j == 0)
		return (cmds);
	(void)new_cmds;
	/*else
	{
		free_cmds(cmds, 0);
		cmds = new_cmds(cmds, i + j, 0, 0);
	}*/
	return (cmds);
}
