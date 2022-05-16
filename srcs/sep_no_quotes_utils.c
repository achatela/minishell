/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_no_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:18:23 by achatela          #+#    #+#             */
/*   Updated: 2022/05/16 13:18:24 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmds_length(char **cmds, int *i, int *j, int *k)
{
	if ((*j) != 0 && (cmds[(*i)][(*j) - 1] == '>'
		|| cmds[(*i)][(*j) - 1] == '<'))
		(*k)++;
	else
		(*k) += 2;
	(*j) += 2;
}

void	cmds_length2(char **cmds, int *i, int *j, int *k)
{
	if ((*j) != 0 && (cmds[(*i)][(*j) - 1] == '>'
		|| cmds[(*i)][(*j) - 1] == '<'))
		(*k)++;
	else
		(*k) += 2;
	(*j)++;
}

char	*new_is_string(char **cmds, int *j, int i)
{
	char	*tmp;

	tmp = new_string(cmds, i, (*j), (*j));
	while (cmds[i] && cmds[i][(*j)]
			&& cmds[i][(*j)] != '<' && cmds[i][(*j)] != '>')
		(*j)++;
	return (tmp);
}

char	*new_is_sep(char **cmds, int *j, int i)
{
	char	*tmp;

	tmp = new_separator(cmds, i, (*j), (*j));
	while (cmds[i] && cmds[i][(*j)]
			&& (cmds[i][(*j)] == '>' || cmds[i][(*j)] == '<'))
		(*j)++;
	return (tmp);
}
