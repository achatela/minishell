#include "minishell.h"

int	check_redir_exist(t_args *args, int i, int fd, char **cmds)
{
	t_args	*head;

	head = args;
	while (args && args->is_separator == 0)
		args = args->next;
	while (args && args->is_separator != 2)
	{
		if (args->is_separator == 1 && ft_strcmp(args->parsed_arg, "<") == 0)
		{
			args = args->next;
			i = access(args->parsed_arg, R_OK);
			if (i == -1)
				return (printf("%s:", args->parsed_arg), 1);
		}
		else if (args->is_separator == 1)
		{
			fd = open_fd(args->next, args->parsed_arg, fd);
			args = args->next;
		}
		else
			args = args->next;
	}
	send_last(head, cmds, fd);
	return (0);
}

void	has_redir_in(t_args *args, char **cmds, int fd)
{
	(void)fd;
	if (check_redir_exist(args, 0, 0, cmds) == 1)
	{
		printf(" no such file or directory\n");
		return ;
	}
}

void	send_last(t_args *args, char **cmds, int fd)
{
	int	old_fd;
	int	new_fd;

	old_fd = dup(1);
	close(1);
	new_fd = dup(fd);
	send_builtin(args, cmds);
	close(new_fd);
	dup(old_fd);
	close(old_fd);
}
