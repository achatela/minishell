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

void	parsing(char *cmd)
{
	char	**cmds;
	t_args	*args;

	cmds = new_parsing(cmd, 0, 0, 0);
	if (cmds == NULL)
	{
		free(cmds);
		return ;
	}
	args = ft_lstnew(NULL);
	fill_args(args, cmds[0], 0);
	args = init_args(args, cmds);
	send_builtin(args, -1, cmds);
	free_list(args);
}
