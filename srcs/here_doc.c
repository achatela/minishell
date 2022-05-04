/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:25:32 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/04 17:46:22 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_sep(t_args *args)
{
	t_args	*head;

	head = args;
	while (head && head->next)
	{
		if (head->is_separator == 1)
			return (1);
		head = head->next;
	}
	if (head->is_separator == 1)
		return (1);
	return (0);
}

static void	here_doc(t_args *args, int i)
{
	char			*delimiter;
	char			*tmp;
	static int		line = 1;

	if (args->next != NULL)
		delimiter = args->next->parsed_arg;
	else
		return ;
	while (i != 1)
	{
		tmp = readline("> ");
		if (tmp == NULL)
		{
			printf("warning: here-document at line %d ", line++);
			printf("delimited by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		else if (ft_strcmp(tmp, delimiter) == 0)
			i = 1;
		free(tmp);
		line++;
	}
}

static void	new_list(t_args *args, char *tmp)
{
	t_args	*head;
	t_args	*head_free;

	head = args;
	while (args && has_sep(args) == 1)
	{
		while (args && ft_strcmp(args->parsed_arg, tmp) != 0)
		{
			head = args;
			args = args->next;
		}
		if (args && ft_strcmp(args->parsed_arg, tmp) == 0)
		{
			args = head;
			head_free = args->next->next;
			head = args->next;
			args->next = args->next->next->next;
			free(head->parsed_arg);
			free(head);
			free(head_free->parsed_arg);
			free(head_free);
		}
		else if (args->next != NULL)
			args = args->next;
	}
}

static void	while_heredoc(t_args *args, char *tmp)
{
	while (args)
	{
		while (args && ft_strcmp(tmp, args->parsed_arg) != 0)
			args = args->next;
		if (args && ft_strcmp(tmp, args->parsed_arg) == 0)
		{
			here_doc(args, 0);
			args = args->next;
		}
	}
}

char	**remove_heredoc(t_args *args, char *tmp, char **cmds)
{
	t_args	*head;
	int		i;

	head = args;
	while_heredoc(args, tmp);
	if (head->next != NULL && head->next->next != NULL)
	{
		new_list(head, tmp);
		cmds = new_cmds(cmds, tmp);
		i = 0;
		while (head)
		{
			head->index = i++;
			head = head->next;
		}
	}
	else
		head->to_use = 2;
	free(tmp);
	return (cmds);
}
