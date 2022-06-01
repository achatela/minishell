/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:06:09 by achatela          #+#    #+#             */
/*   Updated: 2022/06/01 14:05:24 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**has_heredoc(t_args **args, char **cmds)
{
	char	*tmp;
	t_args	*head;

	head = (*args);
	if (head == NULL)
		return (NULL);
	tmp = malloc(sizeof(char) * 3);
	if (!tmp)
		return (NULL);
	tmp[0] = '<';
	tmp[1] = '<';
	tmp[2] = '\0';
	while (head)
	{
		if (ft_strcmp(tmp, head->parsed_arg) == 0)
		{
			cmds = remove_heredoc(args, tmp, cmds);
			return (cmds);
		}
		else
			head = head->next;
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

	pipes = init_pipe(&i, cmds, args);
	while (args)
	{
		if (has_pip(args) == 1)
			fd = pip(pipes, start, fd, 0);
		else
			fd = pip(pipes, start, fd, 1);
		while (args && (args->is_separator == 0
				|| args->is_separator == 1) && i == 0)
			args = while_send_sep(args, &i, pipes->args, cmds);
		if (args && args->is_separator == 0)
			args = skip_cmd(args);
		while (args && args->is_separator == 2)
			args = args->next;
		i = 0;
		pipes->args = args;
		start = 0;
	}
	close(pipes->fd);
	free(pipes);
}

void	while_sep(t_args *args, char **cmds)
{
	int		i;
	t_args	*head;

	i = 0;
	head = args;
	while (args)
	{
		while (args && (args->is_separator == 0 || args->is_separator == 1)
				&& i == 0)
			args = while_send_sep(args, &i, head, cmds);
		i = 0;
		if (args && args->is_separator == 0)
			args = skip_cmd(args);
		while (args && args->is_separator == 2)
			args = args->next;
		head = args;
	}
}

void	parsing(char *cmd)
{
	char	**cmds;
	t_args	*args;

	cmds = NULL;
	args = NULL;
	cmds = init_cmds(cmd, &args);
	if (cmds == NULL)
		return ;
	cmds = has_heredoc(&args, cmds);
	if (error_cmds_args(args, cmds, 0) == 1)
		return ;
	if (has_sep3(args) == 0)
		send_builtin(args, cmds);
	else if (has_pip(args) == 1)
		while_pip(args, 1, 0, cmds);
	else
		while_sep(args, cmds);
	free_cmds(cmds, 0);
	free_list(args);
}
