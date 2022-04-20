#include "minishell.h"

void	redir(t_args *args, char **cmds)
{
	int		fd;
	t_args	*head;

	head = args;
	while (args->is_separator == 0)
		args = args->next;
	while (args->is_separator == 1)
		args = args->next;
	fd = open(args->parsed_arg, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		printf("%s\n", "Error");
	dup2(fd, 1);
	exec_bin(cmds, head);
	close(fd);
}
