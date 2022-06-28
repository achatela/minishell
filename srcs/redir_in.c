/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:39:02 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/08 16:36:49 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_redir(t_args *args)
{
	while (args)
	{
		if (args->parsed_arg[0] == '>' && args->is_separator == 1)
			return (1);
		args = args->next;
	}
	return (0);
}

static char	*get_file_name(t_args *args)
{
	while (args && args->parsed_arg[0] != '<' && args->is_separator != 1)
		args = args->next;
	if (args)
		args = args->next;
	return (args->parsed_arg);
}

static void	not_existing(t_args *args)
{
	int	fd;

	while (args && args->parsed_arg[0] != '<')
	{
		while (args && args->is_separator == 1)
		{
			args = args->next;
		}
		while (args && args->is_separator == 0)
			args = args->next;
		if (args && args->next)
		{
			if (args->parsed_arg[0] == '<')
				break ;
			args = args->next;
		}
		if (args && args->parsed_arg)
		{
			fd = open(args->parsed_arg, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			close(fd);
		}
	}
}

static int	try_access(t_args *sep, t_args *args)
{
	if (ft_strcmp(sep->parsed_arg, ">>") == 0)
		open(args->parsed_arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (ft_strcmp(sep->parsed_arg, ">") == 0)
		open(args->parsed_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
	{
		if (access(args->parsed_arg, R_OK) == -1)
		{
			printf("%s: No such file", args->parsed_arg);
			printf(" or directory\n");
			return (-1);
		}
	}
	return (0);
}

static void	first_redir_out(t_args *args, int i)
{
	while (args && args->is_separator != 2)
	{
		if (args && args->is_separator == 1)
			i = try_access(args, args->next);
		if (i == -1)
			return ;
		else
			args = args->next;
	}
}

static int	has_only_out(t_args *args, t_args *head)
{
	while (args && args->is_separator != 2)
	{
		if (args->is_separator == 1)
		{
			if (args->parsed_arg[0] != '<')
				return (0);
			args = args->next;
		}
		else
			args = args->next;
	}
	return (1);
}

static void	only_out(t_args *args, t_args *head, char **cmds)
{
	char	*tmp;
	int		old_fd;
	int		fd;

	while (args && args->is_separator != 2)
	{
		if (args && args->is_separator == 1)
		{
			tmp = args->next->parsed_arg;
			if (try_access(args, args->next) == -1)
				return ;
			else
				args = args->next;
		}
		else
			args = args->next;
	}
	old_fd = dup(0);
	close(0);
	fd = open(tmp, O_RDONLY);
	send_builtin(head, cmds);
	close(0);
	dup(old_fd);
	close(old_fd);
}

static void	open_right_fd(char *tmp, t_args *head, char **cmds)
{
	int	old_fd;
	int	fd;

	if (ft_strcmp(tmp, "<") == 0)
	{
		old_fd = dup(0);
		close(0);
		fd = open(tmp, O_RDWR);
		send_builtin(head, cmds);
		close(0);
		dup(old_fd);
		close(old_fd);
	}
	/*else
	{
		old_fd = dup(1);
		close(1);
		fd = open(tmp, O_RDWR);
		send_builtin(head, cmds);
		close(1);
		dup(old_fd);
		close(old_fd);
	}*/
}

static int	open_in_out(t_args *sep, t_args *args, t_in_out *fds)
{
	if (fds->in == 0 && ft_strcmp(sep->parsed_arg, "<") == 0)
	{

	}
}

static t_in_out	*init_in_out(void)
{
	t_in_out	*ret;

	ret = malloc(sizeof(t_in_out));
	ret->old_in = dup(0);
	ret->old_out = dup(1);
	ret->in = 0;
	ret->out = 0;
	return (ret);
}

static void	out_in(t_args *args, t_args *head, char **cmds)
{
	char		*tmp;
	t_in_out	*fds;

	fds = init_in_out();
	while (args && args->is_separator != 2)
	{
		if (args && args->is_separator == 1)
		{
			tmp = args->parsed_arg;
			if (try_access(args, args->next) == -1)
			{
				free(fds);
				return ;
			}
			open_in_out(args, args->next, fds);
			args = args->next;
		}
		else
			args =  args->next;
	}
	open_right_fd(tmp, head, cmds);
	free (fds);
}

int	redir_in(t_args *args, t_args *head, char **cmds)
{
	if (ft_strcmp(args->parsed_arg, "<") == 0)
		return (first_redir_out(args, 0), 0);
	else if (has_only_out(args, head) == 1)
		return (only_out(args, args, cmds), 0);
	else
		return (out_in(args, args, cmds), 0);
	//else
	//	return (out_in(args, args, cmds), 0);
	/*char	*tmp;
	int		fd;

	fd = 0;
	if (has_redir(args) == 1)
	{
		tmp = get_file_name(args);
		//if (ft_check_access(tmp, 0) != 0)
		//	return (not_existing(head), 2);
		return (1);
	}
	else
		in_redir(args, head, cmds, fd);
	return (1);*/
}