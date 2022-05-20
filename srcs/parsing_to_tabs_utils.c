/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_to_tabs_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:24:33 by achatela          #+#    #+#             */
/*   Updated: 2022/05/20 17:29:08 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

int	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f' || c == ' ')
		return (1);
	return (0);
}

int	isprintable(char c)
{
	if (c <= 126 && c > 32)
		return (1);
	return (0);
}

int	arg_num_quotes(char *cmd, int *i, int *j, int *k)
{
	(*j) = (*i);
	(*i)++;
	while (cmd[(*i)] && cmd[(*i)] != cmd[(*j)])
		(*i)++;
	if (cmd[(*i)] == '\0')
		return (-1);
	if ((*j) >= 1 && ft_isprint(cmd[(*j) + 1]) == 0)
		(*k)++;
	(*i)++;
	return (0);
}
