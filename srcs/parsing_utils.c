/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:18:43 by achatela          #+#    #+#             */
/*   Updated: 2022/05/24 14:56:23 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*while_send_sep(t_args *args, int *i, t_args *head, char **cmds)
{
	static char	*tmp = NULL;

	if (args && tmp == NULL && args->is_separator == 1)
	{
		tmp = args->parsed_arg;
		send_sep(head, cmds, tmp);
	}
	if (args && args->is_separator == 1
		&& ft_strncmp(tmp, args->parsed_arg, 1) != 0)
	{
		tmp = args->parsed_arg;
		send_sep(head, cmds, tmp);
		(*i) = 1;
	}
	args = args->next;
	if (args && args->is_separator == 2)
		tmp = NULL;
	if (args == NULL)
		tmp = NULL;
	return (args);
}

void	send_sep(t_args *args, char **cmds, char *sep)
{
	if (sep[0] == '>')
	{
		redir(args, cmds, args, 0);
		return ;
	}
	if (sep[0] == '<' && sep[1] == '\0')
	{
		redir_in(args, args, cmds);
		return ;
	}
}

int	arg_number(char *cmd, int i, int j)
{
	if (cmd[i] != ' ' && ft_isprint(cmd[i]) == 1)
		j++;
	while (cmd[i])
	{
		if (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == '\n'
			|| cmd[i] == '\r' || cmd[i] == '\v' || cmd[i] == '\v')
		{
			if (cmd[i + 1] != ' ' && ft_isprint(cmd[i + 1]) == 1)
				j++;
			i++;
		}
		else if (cmd[i + 1] != ' ' && ft_isprint(cmd[i + 1]) == 1)
			i++;
		else
			i++;
	}
	return (j);
}

char	**init_cmds(char *cmd, t_args **args)
{
	char	**cmds;

	cmds = parsing_to_tabs(cmd, init_idx(0, 0, 0, 0));
	if (cmds == NULL || cmds[0] == 0)
	{
		free(cmds);
		return (NULL);
	}
	cmds = parse_separators(cmds, 0);
	(*args) = ft_lstnew(NULL);
	fill_args((*args), cmds[0], 0, "|");
	(*args) = init_args((*args), cmds);
	if (sep_error((*args), cmds, (*args)) == -1)
	{
		builtin_export(g_env, ft_export(2, "export"));
		return (NULL);
	}
	return (cmds);
}

int	sep_error(t_args *args, char **cmds, t_args *head)
{
	if (head->is_separator == 2)
	{
		printf("syntax error near unexepected token `|'\n");
		return (free_cmds(cmds, 0), free_list(head), -1);
	}
	while (args)
	{
		if (args->is_separator != 0 && args->next == NULL)
		{
			printf("syntax error near unexpected token `newline'\n");
			return (free_cmds(cmds, 0), free_list(head), -1);
		}
		else if ((args->is_separator == 1 && args->next->is_separator == 2)
			|| (args->is_separator == 2 && args->next->is_separator == 2))
		{
			printf("syntax error near unexepected token `|'\n");
			return (free_cmds(cmds, 0), free_list(head), -1);
		}
		else if (args->is_separator == 1 && args->next->is_separator == 1)
			return (error_double_redir(cmds, args, head));
		args = args->next;
	}
	return (0);
}
