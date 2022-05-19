/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:06:09 by achatela          #+#    #+#             */
/*   Updated: 2022/05/19 16:53:59 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**has_heredoc(t_args *args, char **cmds)
{
	char	*tmp;
	t_args	*head;

	head = args;
	if (head == NULL)
		return (NULL);
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

static int	has_sep3(t_args *args)
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

static void	while_pip(t_args *args, int start, int fd, char **cmds)
{
	int		i;
	t_pipe	*pipes;

	pipes = malloc(sizeof(t_pipe));
	pipes->cmds = cmds;
	pipes->args = args;
	i = 0;
	while (args)
	{
		if (has_pip(args) == 1)
			fd = pip(pipes, start, fd, 0);
		else
			fd = pip(pipes, start, fd, 1);
		while (args && (args->is_separator == 0
				|| args->is_separator == 1) && i == 0)
			args = while_send_sep(args, &i, pipes->args, cmds);
		i = 0;
		while (args && args->is_separator == 2)
			args = args->next;
		pipes->args = args;
		start = 0;
	}
	free(pipes);
}

void	parsing(char *cmd)
{
	char	**cmds;
	t_args	*head;
	t_args	*args;

	cmds = NULL;
	args = NULL;
	cmds = init_cmds(cmd, &args);
	if (cmds == NULL)
		return ;
	head = args;
	cmds = has_heredoc(args, cmds);
	head = args;
	if (args->to_use == 2)
	{
		free_list(args);
		free_cmds(cmds, 0);
		return ;
	}
	if (has_sep3(args) == 0)
		send_builtin(args, cmds);
	else if (has_sep3(args) == 1)
		while_pip(args, 1, 0, cmds);
	free_cmds(cmds, 0);
	free_list(head);
}
