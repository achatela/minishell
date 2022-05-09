/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:58:37 by achatela          #+#    #+#             */
/*   Updated: 2022/05/09 13:12:02 by achatela         ###   ########.fr       */
/*   Updated: 2022/05/06 15:59:49 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_last(t_args *args)
{
	while (args)
	{
		while (args && args->is_separator == 0)
			args = args->next;
		if (args && args->is_separator == 1)
		{
			if ((args->parsed_arg[0] == '>' && args->parsed_arg[1] == '>'
					&& args->parsed_arg[2] == '\0')
				|| (args->parsed_arg[0] == '>' && args->parsed_arg[1] == '\0'))
				return (1);
			else if (args->parsed_arg[0] == '<')
				return (0);
		}
		else if (args && args->is_separator == 2)
			return (2);
		else
			return (0);
	}
	return (0);
}

static void	create_while(t_args *create, int fd)
{
	while (create && is_last(create) != 0 && create->next->is_separator != 2)
	{
		while (create && create->is_separator == 1)
			create = create->next;
		while (create && create->is_separator == 0)
			create = create->next;
		if (create && create->next)
			create = create->next;
		if (create && create->parsed_arg)
		{
			if (create->is_separator != 2)
			{
				fd = open(create->parsed_arg, O_CREAT, 0644);
				close(fd);
			}
		}
	}
}

static int	open_fd(t_args *args, char *tmp)
{
	int	fd;

	fd = 0;
	if (tmp[0] && tmp[1] == '\0')
		fd = open(args->parsed_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(args->parsed_arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd);
}

void	redir(t_args *args, char **cmds, t_args *head, int fd)
{
	int		old_fd;
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
	create_while(head, fd);
	if (ft_check_access(args->parsed_arg, 0) == -1)
		return ;
	if (tmp == NULL)
		tmp = args->parsed_arg;
	old_fd = dup(1);
	close(1);
	fd = open_fd(args, tmp);
	if (fd < 0)
		printf("%s\n", "Cannot open fd");
	send_builtin(head, 0, cmds);
	close(1);
	dup(old_fd);
}
