#include "minishell.h"

static int	check_echo(t_args *args, int i)
{
	(void)args;
	(void)i;
	return (0);
}

static void print_n(t_args *args)
{
	args = args->next;
	while (args && args->to_use == 1)
	{
		printf("%s", args->parsed_arg);
		args = args->next;
		if (args != NULL && args->to_use == 1)
			printf(" ");
	}
}

int	builtin_echo(t_args *args)
{
	if (check_echo(args, 0) == -1)
		return (-1);
	if (args->next != NULL)
	{
		if (args->next->parsed_arg[0] == '-' 
			&& args->next->parsed_arg[1] == 'n')
		{
			print_n(args->next);
			return (1);
		}
	}
	args = args->next;
	while (args && args->to_use == 1)
	{
		printf("%s", args->parsed_arg);
		printf(" ");
		args = args->next;
	}
	printf("\n");
	return (1);
}
