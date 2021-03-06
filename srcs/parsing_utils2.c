/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:53:29 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/21 13:44:43 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_double_redir(char **cmds, t_args *args, t_args *head)
{
	printf("syntax error near unexepected token ");
	printf("`%s'\n", args->next->parsed_arg);
	free_cmds(cmds, 0);
	free_list(head);
	return (-1);
}

int	error_cmds_args(t_args *args, char **cmds, int i)
{
	if (cmds == NULL)
	{
		free_list(args);
		return (1);
	}
	if (args->to_use == 2)
	{
		free_list(args);
		free_cmds(cmds, i);
		return (1);
	}
	return (0);
}

t_pipe	*init_pipe(int *i, char **cmds, t_args *args)
{
	t_pipe	*pipes;

	pipes = malloc(sizeof(t_pipe));
	pipes->cmds = cmds;
	pipes->args = args;
	(*i) = 0;
	return (pipes);
}

t_args	*skip_cmd(t_args *args)
{
	while (args && args->is_separator != 2)
		args = args->next;
	if (args)
		args = args->next;
	return (args);
}

char	*while_send_sep2(t_args *args, char *tmp)
{
	if (args && (args->next == NULL || args->is_separator == 2))
		tmp = NULL;
	if (args == NULL)
		tmp = NULL;
	return (tmp);
}
