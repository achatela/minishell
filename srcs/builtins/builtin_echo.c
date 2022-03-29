#include "minishell.h"

static int	check_echo(char **cmds, int i)
{
	(void)cmds;
	(void)i;
	return (0);
}

static void print_n(char **cmds, int i)
{
	while (cmds[i] != NULL)
	{
		printf("%s", cmds[i]);
		i++;
		if (cmds[i] != NULL)
			printf(" ");
	}
}

int	builtin_echo(char **cmds, int i)
{
	if (check_echo(cmds, 0) == -1)
		return (-1);
	if (cmds[1] != NULL)
	{
		if (cmds[1][0] == '-' && cmds[1][1] == 'n')
		{
			print_n(cmds, 2);
			return (1);
		}
	}
	while (cmds[i] != NULL)
	{
		printf("%s", cmds[i]);
		printf(" ");
		i++;
	}
	printf("\n");
	return (1);
}
