/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:59:16 by achatela          #+#    #+#             */
/*   Updated: 2022/05/16 14:08:53 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
