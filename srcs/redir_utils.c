/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:42:11 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/20 17:57:45 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_access_redir(char *file)
{
	if (access(file, F_OK) == -1 || access(file, R_OK == -1))
	{
		printf("%s: No such file or directory\n", file);
		return (-1);
	}
	else if (access(file, W_OK) == -1)
	{
		printf("%s: Permission denied\n", file);
		return (-1);
	}
	return (0);
}

void	redir2(t_args *head, int old_fd, char **cmds)
{
	if (head->next->next)
		send_builtin(head->next->next, cmds);
	close(1);
	dup(old_fd);
	close(old_fd);
}
