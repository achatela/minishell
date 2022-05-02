/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:30:54 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/02 16:31:14 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_is_sep(char *str)
{
	if (ft_strlen(str) > 3)
		return (0);
	else if (str[0] == '|' && str[1] == '\0')
		return (1);
	else if (str[0] == '<' && str[1] == '\0')
		return (1);
	else if (str[0] == '>' && str[1] == '\0')
		return (1);
	else if (str[0] == '<' && str[1] == '<'
		&& str[2] == '\0')
		return (1);
	else if (str[0] == '>' && str[1] == '>'
		&& str[2] == '\0')
		return (1);
	else
		return (0);
}

void	fill_args(t_args *args, char *str, int index, char *pip)
{
	if (index == 0)
	{
		args->to_use = 0;
		args->is_command = 1;
	}
	else if (index > 0)
	{
		args->to_use = 1;
		args->is_command = 0;
	}
	args->is_separator = 0;
	if (ft_strcmp(str, pip) == 0)
		args->is_separator = 2;
	else if (str_is_sep(str) == 1)
		args->is_separator = 1;
	args->index = index;
	args->parsed_arg = parse_arg(str, 0);
}

t_args	*init_args(t_args *args, char **cmds, t_echo *echo)
{
	int		i;
	t_args	*head;

	i = 1;
	while (cmds[i] != NULL && cmds[i][0] != '\0')
	{
		ft_lstadd_back(args, ft_lstnew(NULL));
		fill_args(ft_lstlast(args), cmds[i], i, "|");
		i++;
	}
	i = 0;
	head = args;
	head->echo = echo;
	while (head)
	{
		free(cmds[i]);
		head->echo = echo;
		cmds[i] = ft_strdup(head->parsed_arg);
		i++;
		head = head->next;
	}
	free(cmds[i]);
	cmds[i] = 0;
	return (args);
}
