/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:30:46 by achatela          #+#    #+#             */
/*   Updated: 2022/06/22 16:35:56 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	*init_pips(int i)
{
	t_fd	*ret;

	ret = malloc(sizeof(t_fd));
	ret->i = i;
	ret->tmpin = dup(STDIN_FILENO);
	ret->tmpout = dup(STDOUT_FILENO);
	return (ret);
}

int	is_builtin(t_pipe *pipes)
{
	if (!pipes->cmds || !pipes->cmds[0])
		return (0);
	if (ft_strcmp(pipes->cmds[0], "echo") == 0)
		return (1);
	if (ft_strcmp(pipes->cmds[0], "cd") == 0)
		return (1);
	if (ft_strcmp(pipes->cmds[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(pipes->cmds[0], "env") == 0)
		return (1);
	if (ft_strcmp(pipes->cmds[0], "export") == 0)
		return (1);
	if (ft_strcmp(pipes->cmds[0], "unset") == 0)
		return (1);
	if (ft_strcmp(pipes->cmds[0], "exit") == 0)
		return (1);
	return (0);
}
