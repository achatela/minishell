/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:25:32 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/31 17:38:12 by achatela         ###   ########.fr       */
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
	sigaction(SIGQUIT, &act, NULL);
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

static t_args	*new_list(t_args *args, char **cmds)
{
	t_args	*new;

	new = ft_lstnew(NULL);
	if (cmds[0] == 0)
	{
		new->to_use = 2;
		new->parsed_arg = ft_strdup("free");
		free_list(args);
		return (new);
	}
	fill_args(new, cmds[0], 0, "|");
	new = init_args(new, cmds);
	free_list(args);
	return (new);
}

static void	while_heredoc(t_args *args, char *tmp)
{
	t_args	*head;

	head = args;
	while (head)
	{
		while (head && ft_strcmp(tmp, head->parsed_arg) != 0)
			head = head->next;
		if (head && ft_strcmp(tmp, head->parsed_arg) == 0)
		{
			here_doc(head, 0, 1, NULL);
			head = head->next;
		}
	}
}

char	**remove_heredoc(t_args **args, char *tmp, char **cmds)
{
	while_heredoc((*args), tmp);
	if ((*args)->next != NULL && (*args)->next->next != NULL)
	{
		cmds = new_cmds(cmds, tmp);
		(*args) = new_list((*args), cmds);
	}
	else
		(*args)->to_use = 2;
	free(tmp);
	tmp = get_env_var(g_env, "?", 0);
	if (tmp != NULL && ft_strcmp(tmp, "0") != 0)
	{
		free(tmp);
		free_cmds(cmds, 0);
		return (NULL);
	}
	if (tmp != NULL)
		free(tmp);
	return (cmds);
}
