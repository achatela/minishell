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
	while (args && ft_strlen(args->parsed_arg) == 2 
			&& args->parsed_arg[0] == '-' && args->parsed_arg[1] == 'n'
			&& args->parsed_arg[2] == '\0')
		args = args->next;
	while (args && args->to_use == 1
			&& args->is_separator == 0)
	{
		printf("%s", args->parsed_arg);
		args = args->next;
		if (args != NULL && args->is_separator == 0)
			printf(" ");
	}
}

int	builtin_echo(t_args *args)
{
	int fd;
	if (check_echo(args, 0) == -1)
		return (-1);
	if (args->next != NULL && ft_strlen(args->next->parsed_arg) > 1)
	{
		if (args->next->parsed_arg[0] == '-' 
			&& args->next->parsed_arg[1] == 'n')
		{
			print_n(args->next);
			return (1);
		}
	}
	args = args->next;
	while (args && args->to_use == 1 && args->is_separator == 0)
	{
		printf("%s", args->parsed_arg);
		printf(" ");
		args = args->next;
	}
	if (args && args->to_use == 1 && args->is_separator == 1)
	{
		fd = open(args->next->parsed_arg, O_WRONLY | O_CREAT, 0666);
		if (fd < 0)
		{
			printf("file not found\n");
			return (2);
		}
		write(fd, "ff\n", 3); // OUE
		close(fd);
	}
	printf("\n");
	return (1);
}
