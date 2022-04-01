#include "minishell.h"

int	arg_number(char *cmd, int i, int j)
{
	if (cmd[i] != ' ' && ft_isprint(cmd[i]) == 1)
		j++;
	while (cmd[i])
	{
		if (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == '\n'
			|| cmd[i] == '\r' || cmd[i] == '\v' || cmd[i] == '\v')
		{
			if (cmd[i + 1] != ' ' && ft_isprint(cmd[i + 1]) == 1)
				j++;
			i++;
		}
		else if (cmd[i + 1] != ' ' && ft_isprint(cmd[i + 1]) == 1)
			i++;
		else
			i++;
	}
	return (j);
}

char	**parsing(char *cmd)
{
	char	**cmds;
	t_args	*args;
	t_args	*head;

	args = NULL;
	cmds = str_to_tabs(cmd, 0, 0);
	if (cmds[0] == NULL)
	{
		free(cmds);
		return (NULL);
	}
	args = init_args(args, cmds);
	head = args;
	while (head)
	{
		printf("parsed arg = %s index = %d\n", head->parsed_arg, head->index);
		head = head->next;
	}
	send_builtin(cmds);
	return (cmds);
}
