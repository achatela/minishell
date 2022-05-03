/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:39:02 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/03 19:00:11 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	last_redir_in(t_args *args)
{
	while (args)
	{
		while (args && args->is_separator == 0)
			args = args->next;
		if (args && args->is_separator == 1)
		{
			if (args->parsed_arg[0] == '<' && args->parsed_arg[1] == '\0')
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

void	redir_in(t_args *args, char **cmds)
{
	t_args	*head;
	int		fd;
	int		old_fd;

	head = args;
	while (args && last_redir_in(args) != 0 && args->next->is_separator != 2)
	{
		while (args && args->is_separator == 0)
		{
			args = args->next;
		}
		while (args && args->is_separator == 1)
		{
			args = args->next;
		}
		if (access(args->parsed_arg, R_OK) == -1)
		{
			printf("%s: No such file or directory\n", args->parsed_arg);
			return ;
		}
		old_fd = dup(0);
		close(0);
		fd = open(args->parsed_arg, O_RDONLY);
		if (fd < 0)
		{
			close(0);
			dup(old_fd);
			return ;
		}
		send_builtin(head, 0, cmds);
	//	exec_bin(cmds, head);
		close(0);
		dup(old_fd);
	}
}
