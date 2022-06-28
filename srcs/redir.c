/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:58:37 by achatela          #+#    #+#             */
/*   Updated: 2022/06/20 17:48:23 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_while_sep(t_args *create, int fd)
{
	while (create && is_last(create) != 0 && create->next->is_separator != 2)
	{
		while (create && create->is_separator == 1)
			create = create->next;
		if (create && create->parsed_arg)
		{
			if (create->is_separator != 2)
			{
				fd = open(create->parsed_arg, O_WRONLY
						| O_TRUNC | O_CREAT, 0644);
				close(fd);
			}
		}
		while (create && create->is_separator == 0)
			create = create->next;
	}
}

static void	create_while(t_args *create, int fd)
{
	if (create->is_separator == 0)
	{
		while (create && is_last(create) != 0
			&& create->next->is_separator != 2)
		{
			while (create && create->is_separator == 1)
				create = create->next;
			while (create && create->is_separator == 0)
				create = create->next;
			if (ft_strcmp(create->parsed_arg, "<") == 0)
					return ;
			if (create && create->next)
				create = create->next;
			if (create && create->parsed_arg && is_last(create) != 0)
			{
				fd = open(create->parsed_arg, O_WRONLY
						| O_TRUNC | O_CREAT, 0644);
				close(fd);
			}
		}
		fd = open(create->parsed_arg, O_CREAT, 0644);
		close(fd);
	}
	else
		create_while_sep(create, fd);
}

static int	has_redir_only(t_args *args)
{
	while (args && args->is_separator != 2)
	{
		if (args && args->parsed_arg[0] == '<' && args->is_separator == 1)
			return (1);
		args = args->next;
	}
	//if (args && args->is_separator == 2)
	//	return (1);
	return (0);
}

static void	redir_only(t_args *args, char **cmds, int fd)
{
	int	old_fd;

	if (ft_strcmp(args->parsed_arg, ">") == 0)
	{
		create_while_sep(args, 0);
		redir2(args, args, 0, cmds);
		return ;
	}
	else
		create_while(args, 0);
	old_fd = dup(1);
	close(1);
	fd = open_fd(get_args(args), get_sep(args), 0);
	send_builtin(args, cmds);
	close(1);
	dup(old_fd);
	close(old_fd);
}

static void	send_last(t_args *args, char **cmds, int fd)
{
	int	old_fd;
	int	new_fd;

	old_fd = dup(1);
	close(1);
	new_fd = dup(fd);
	send_builtin(args, cmds);
	close(1);
	dup(old_fd);
	close(old_fd);
}

static int	check_redir_exist(t_args *args, int i, int fd, char **cmds)
{
	t_args	*head;

	head = args;
	while (args && args->is_separator == 0)
		args = args->next;
	while (args && args->is_separator != 2)
	{
		if (args->is_separator == 1 && ft_strcmp(args->parsed_arg, "<") == 0)
		{
			args = args->next;
			i = access(args->parsed_arg, R_OK);
			if (i == -1)
				return (printf("%s:", args->parsed_arg), 1);
		}
		else if (args->is_separator == 1)
		{
			fd = open_fd(args->next, args->parsed_arg, fd);
			args = args->next;
		}
		else
			args = args->next;
	}
	send_last(head, cmds, fd);
	return (0);
}

static void	has_redir_in(t_args *args, char **cmds, int fd)
{
	if (check_redir_exist(args, 0, 0, cmds) == 1)
	{
		printf(" no such file or directory\n");
		return ;
	}
}

void	redir(t_args *args, char **cmds, t_args *head, int fd)
{
	char	*tmp;

	(void)head;
	if (has_redir_only(args) == 0)
		redir_only(args, cmds, fd);
	else
		has_redir_in(args, cmds, fd);
			//redir_only(args, cmds);
	/*printf("une fois normalement ?\n");
	args = get_args(args);
	tmp = get_sep(head);
	create_while(head, fd);
	if (ft_check_access_redir(args->parsed_arg) == -1)
		return ;
	old_fd = dup(1);
	close(1);
	fd = open_fd(args, tmp);
	if (fd < 0)
	{
		close(1);
		dup(old_fd);
		close(old_fd);
		printf("%s\n", "Cannot open fd");
		return ;
	}
	if (head->is_separator == 0)
		send_builtin(head, cmds);
	redir2(head, old_fd, cmds);*/
}
