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

static int	has_sep(t_args *args)
{
	t_args	*head;

	head = args;
	while (head)
	{
		if (head && head->is_separator && (head->is_separator == 1 || head->is_separator == 2))
			return (1);
		head = head->next;
	}
	return (0);
}

static char **has_heredoc(t_args *args, char **cmds)
{
	char	*tmp;
	t_args	*head;

	head = args;
	tmp = malloc(sizeof(char) * 3);
	if (!tmp)
		return (NULL);
	tmp[0] = '<';
	tmp[1] = '<';
	tmp[2] = '\0';
	while (args)
	{
		if (ft_strcmp(tmp, args->parsed_arg) == 0)
		{
			cmds = remove_heredoc(head, tmp, cmds);
			return (cmds);
		}
		else
			args = args->next;
	}
	free(tmp);
	return (cmds);
}

void	parsing(char *cmd, t_echo *echo)
{
	char	**cmds;
	t_args	*head;
	t_args	*args;
	t_args	*free_head;
	int		start = 1;
	int		fd = 0;

	cmds = new_parsing(cmd, 0, 0, 0);
	if (cmds == NULL || cmds[0] == 0)
	{
		free(cmds);
		return ;
	}
	cmds = parse_separators(cmds, 0);
	args = ft_lstnew(NULL);
	fill_args(args, cmds[0], 0, "|");
	args = init_args(args, cmds, echo);
	free_head = args;
	cmds = has_heredoc(args, cmds);
	if (args->to_use == 2)
	{
		free_list(args);
		free_cmds(cmds, 0);
		return ;
	}
	if (has_sep(args) == 0)
		send_builtin(args, -1, cmds);
	else if (has_sep(args) == 1)
	{
		head = args;
		while (args && has_sep(args) == 1)
		{
			fd = pip(head, start, fd, 0, cmds);
			while (args && args->is_separator == 0)
				args = args->next;
			while (args && args->is_separator == 2)
				args = args->next;
			head = args;
			start = 0;
			/*while (args && args->is_separator == 0)
				args = args->next;
			if (args && args->next && args->is_separator == 1)
			{
				while (args && args->is_separator == 1)
					args = args->next;
			}
			if (head->is_separator != 1)
				send_builtin(head, -1, cmds);
			else
				args = args->next;
			head = args;*/
		}
		fd = pip(head, start, fd, 1, cmds);
	}
	free_cmds(cmds, 0);
	free_list(free_head);
}
