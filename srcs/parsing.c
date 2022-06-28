/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:06:09 by achatela          #+#    #+#             */
/*   Updated: 2022/06/21 14:49:51 by cjimenez         ###   ########.fr       */
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

int	has_pip(t_args *args)
{
	t_args	*head;

	head = args;
	while (head && head->next)
	{
		head = head->next;
		if (head->is_separator == 2)
			return (1);
	}
	return (0);
}

static void	while_pip(t_args *args, char **cmds)
{
	int		i;
	t_pipe	*pipes;
	t_fd	*pips;

	pips = init_pips(0);
	pipes = init_pipe(&i, cmds, args);
	pipes->fd = pip(pipes, pips);
	free(pipes);
	free(pips);
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
		while_pip(args, cmds);
	else
		send_to_sep(args, args, cmds);
		//send_builtin(args, cmds);
		//redir_in(args, args, cmds);
		//redir(args, cmds, args, 0);
		//while_sep(args, cmds);
	free_cmds(cmds, 0);
	free_list(args);
}