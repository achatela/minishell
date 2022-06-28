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

char	*get_sep(t_args *args)
{
	char	*tmp;

	while (args && is_last(args) != 0 && args->next->is_separator != 2)
	{
		while (args && args->is_separator == 0)
			args = args->next;
		while (args && args->is_separator == 1)
		{
			tmp = args->parsed_arg;
			args = args->next;
		}
	}
	return (tmp);
}

int	open_fd(t_args *args, char *tmp, int fd)
{
	if (fd != 0)
		close(fd);
	if (tmp[0] && tmp[1] == '\0')
		fd = open(args->parsed_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(args->parsed_arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd);
}

void	redir2(t_args *args, t_args *head, int old_fd, char **cmds)
{
	int	fd;

	old_fd = dup(1);
	close(1);
	fd = open_fd(get_args(args), get_sep(args), 0);
	if (head->next->next)
		send_builtin(head->next->next, cmds);
	close(fd);
	dup(old_fd);
	close(old_fd);
}
