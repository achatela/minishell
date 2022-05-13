/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:06:09 by achatela          #+#    #+#             */
/*   Updated: 2022/05/13 14:48:04 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (head && (head->is_separator == 1 || head->is_separator == 2))
			return (1);
		head = head->next;
	}
	return (0);
}

static char	**has_heredoc(t_args *args, char **cmds)
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

static int	has_pip(t_args *args)
{
	t_args	*head;

	head = args;
	while (head)
	{
		if (head->is_separator == 2)
			return (1);
		head = head->next;
	}
	return (0);
}

static void	send_sep(t_args *args, char **cmds, char *sep)
{
	if (sep[0] == '>')
	{
		redir(args, cmds, args, 0);
		return ;
	}
	if (sep[0] == '<' && sep[1] == '\0')
	{
		redir_in(args, args, cmds);
		return ;
	}
}

static void	while_pip(t_args *args, int start, int fd, char **cmds)
{
	t_args	*head;
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	head = args;
	while (args)
	{
		if (has_pip(args) == 1)
			fd = pip(head, start, fd, 0, cmds);
		else
			fd = pip(head, start, fd, 1, cmds);
		while (args && (args->is_separator == 0
				|| args->is_separator == 1) && i == 0)
		{
			if (args && tmp == NULL && args->is_separator == 1)
			{
				tmp = args->parsed_arg;
				send_sep(head, cmds, tmp);
			}
			if (args && args->is_separator == 1
				&& ft_strncmp(tmp, args->parsed_arg, 1) != 0)
			{
				tmp = args->parsed_arg;
				send_sep(head, cmds, tmp);
				i = 1;
			}
			args = args->next;
		}
		i = 0;
		while (args && args->is_separator == 2)
			args = args->next;
		head = args;
		tmp = NULL;
		start = 0;
	}
}

static void	test_boucle_pipe(t_args *args, int start, int fd, char **cmds)
{
	t_args		*head;
	char		*tmp;
	int			i;

	head = args;
	tmp = NULL;
	i = 0;
	if (has_pip(args) == 0)
	{
		while (args && i == 0)
		{
			while (args && (args->is_separator == 0 || args->is_separator == 1))
			{
				if (args && tmp == NULL && args->is_separator == 1 && i == 0)
				{
					tmp = args->parsed_arg;
					send_sep(head, cmds, tmp);
				}
				if (args && args->is_separator == 1
					&& ft_strncmp(tmp, args->parsed_arg, 1) != 0 && i == 0)
				{
					tmp = args->parsed_arg;
					send_sep(head, cmds, tmp);
					i = 1;
				}
				args = args->next;
			}
		}
		return ;
	}
	while_pip(args, start, fd, cmds);
}

static int	sep_error(t_args *args, char **cmds)
{
	t_args	*head;

	head = args;
	while (args)
	{
		if (args->is_separator != 0 && args->next == NULL)
		{
			printf("syntax error near unexpected token `newline'\n");
			free_cmds(cmds, 0);
			free_list(head);
			return (-1);
		}
		else if ((args->is_separator == 1 && args->next->is_separator == 2)
			|| (args->is_separator == 2 && args->next->is_separator == 2))
		{
			printf("syntax error near unexepected token `|'\n");
			free_cmds(cmds, 0);
			free_list(head);
			return (-1);
		}
		else if (args->is_separator == 1 && args->next->is_separator == 1)
		{
			printf("syntax error near unexepected token ");
			printf("`%s'\n", args->next->parsed_arg);
			free_cmds(cmds, 0);
			free_list(head);
			return (-1);
		}
		args = args->next;
	}
	return (0);
}

void	parsing(char *cmd, t_echo *echo)
{
	char	**cmds;
	t_args	*head;
	t_args	*args;
	int		start;
	int		fd;

	start = 1;
	fd = 0;
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
	if (sep_error(args, cmds) == -1)
	{
		args->echo->print = 2;
		return ;
	}
	head = args;
	cmds = has_heredoc(args, cmds);
	head = args;
	if (args->to_use == 2)
	{
		free_list(args);
		free_cmds(cmds, 0);
		return ;
	}
	if (has_sep(args) == 0)
		send_builtin(args, cmds);
	else if (has_sep(args) == 1)
		test_boucle_pipe(args, start, fd, cmds);
	free_cmds(cmds, 0);
	free_list(head);
}
