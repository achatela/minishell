/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:25:32 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/17 16:12:32 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_delimiter(char *delimiter, t_args *args)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_sigaction = heredoc_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	delimiter = args->next->parsed_arg;
	return (delimiter);
}

static void	here_doc(t_args *args, int i, pid_t pid, char *delimiter)
{
	char				*tmp;
	static int			line = 1;

	pid = fork();
	if (pid == 0)
	{
		delimiter = get_delimiter(delimiter, args);
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
		exit(0);
	}
	else
		waitpid(pid, 0, 0);
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
		else if (args && args->next != NULL)
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
			here_doc(args, 0, 1, NULL);
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
