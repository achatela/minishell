#include "minishell.h"

static int	check_echo(char **argv, int i)
{
	return (0);
}

static void print_n(char **argv, int i)
{
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

int	builtin_echo(char **argv, int i)
{
	if (check_echo(argv, 0) == -1)
		return (-1);
	if (argv[1][0] == '-' && argv[1][1] == 'n')
	{
		print_n(argv, 2);
		return (1);
	}
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		printf(" ");
		i++;
	}
	printf("\n");
	return (1);
}
