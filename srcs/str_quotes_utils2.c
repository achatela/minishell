/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_quotes_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:19:16 by achatela          #+#    #+#             */
/*   Updated: 2022/05/20 13:51:37 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_tmp(char *str, int i, int j)
{
	int		k;
	char	*tmp;
	char	*tmp2;

	tmp = malloc(sizeof(char) * (j - i) + 2);
	i++;
	k = -1;
	while (++k > -1 && i < j)
		tmp[k] = str[i++];
	tmp[k++] = '=';
	tmp[k] = '\0';
	tmp2 = get_env_var(g_env, tmp, 0);
	free(tmp);
	return (tmp2);
}

void	length_d_dollar(char *str, int *i, int *length)
{
	(*length) += var_d_length(str, (*i), (*i) + 1, -1);
	if (var_d_length(str, (*i), (*i) + 1, -1) == -1)
	{
		(*length) += 3;
		(*i) += 2;
		return ;
	}
	(*i)++;
	if (str[(*i)] && str[(*i)] == '?')
		(*i)++;
	else
	{
		while (str[(*i)] && (ft_isalpha(str[(*i)]) == 1
				|| ft_isalnum(str[(*i)]) == 1
				|| str[(*i)] == '_'))
			(*i)++;
	}
}
