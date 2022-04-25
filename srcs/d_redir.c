#include "minishell.h"

static int	d_is_last(t_args *args)
{
	while (args)
	{
		while (args && args->is_separator == 0)
			args = args->next;
		if (args && args->is_separator == 1)
		{
			if (args->parsed_arg[0] == '>' && args->parsed_arg[1] == '>'
				&& args->parsed_arg[2] == '\0')
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

void	d_redir(t_args *args, char **cmds)
{
	int		fd;
	int		old_fd;
	t_args	*head;
	t_args	*create;

	head = args;
	create = head;
	while (args && d_is_last(args) != 0)
	{
		while (args && args->is_separator == 0)
			args = args->next;
		while (args && args->is_separator == 1)
			args = args->next;
	}
	while (create && d_is_last(create) != 0)
	{
		while (create && create->is_separator == 1)
			create = create->next;
		while (create && create->is_separator == 0)
			create = create->next;
		if (create && create->next)
			create = create->next;
		if (create && create->parsed_arg)
		{
			fd = open(create->parsed_arg, O_CREAT, 0644);
			close(fd);
		}
	}
	old_fd = dup(1);
	close(1);
	fd = open(args->parsed_arg, O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		printf("%s\n", "Error");
	exec_bin(cmds, head);
	close(1);
	dup(old_fd);
}
