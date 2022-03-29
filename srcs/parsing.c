#include "minishell.h"

int	arg_number(char *cmd, int i, int j)
{
	if (ft_isalpha(cmd[i]) == 1 || ft_isalnum(cmd[i]) == 1)
		j++;
	while (cmd[i])
	{
		if (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == '\n'
			|| cmd[i] == '\r' || cmd[i] == '\v' || cmd[i] == '\v')
		{
			if (ft_isalpha(cmd[i + 1]) == 1 || ft_isalnum(cmd[i + 1]) == 1)
				j++;
			i++;
		}
		else if (ft_isalpha(cmd[i] == 1) || ft_isalnum(cmd[i + 1]) == 1)
			i++;
		else
			i++;
	}
	return (j);
}

void	parsing(char *cmd)
{
	char	**cmds;

	cmds = str_to_tabs(cmd, 0, 0, 0);
	if (cmds[0] == NULL)
	{
		free(cmds);
		return ;
	}
	send_builtin(cmds);
	return ;
}
