/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:59:16 by achatela          #+#    #+#             */
/*   Updated: 2022/05/18 17:49:03 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spaces(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		return (1);
	return (0);
}

int	has_sep(t_args *args)
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

int	is_shlvl(char *str)
{
	if (str[0] == 'S' && str[1] == 'H' && str[2] == 'L'
		&& str[3] == 'V' && str[4] == 'L' && str[5] == '=')
		return (1);
	return (0);
}

t_index	*init_idx(int i, int j, int k, int l)
{
	t_index	*idx;

	idx = malloc(sizeof(t_index));
	idx->i = i;
	idx->j = j;
	idx->k = k;
	idx->l = l;
	return (idx);
}

t_args	*ft_export(int value, char *export)
{
	t_args	*lst;
	char	*tmp;

	lst = ft_lstnew(NULL);
	lst->to_use = 4;
	lst->parsed_arg = ft_strdup(export);
	lst->next = ft_lstnew(NULL);
	lst->next->parsed_arg = malloc(sizeof(char) * 3);
	lst->next->to_use = 1;
	lst->next->is_command = 4;
	lst->next->is_separator = 0;
	lst->next->parsed_arg[0] = '?';
	lst->next->parsed_arg[1] = '=';
	lst->next->parsed_arg[2] = '\0';
	tmp = ft_itoa(value);
	lst->next->parsed_arg = ft_strjoin(lst->next->parsed_arg, tmp);
	free(tmp);
	return (lst);
}
