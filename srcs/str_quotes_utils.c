/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_quotes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:09:44 by achatela          #+#    #+#             */
/*   Updated: 2022/05/19 19:14:25 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fill_tmp(char *str, t_index *idx, int j)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = malloc(sizeof(char) * ((j - idx->i) + 2));
	idx->i++;
	while (++idx->k > -1 && idx->i < j)
		tmp2[idx->k] = str[idx->i++];
	tmp2[idx->k++] = '=';
	tmp2[idx->k] = '\0';
	tmp = get_env_var(g_env, tmp2, 0);
	free(tmp2);
	return (tmp);
}

void	var_str(char *str, t_index *idx, char *ret)
{
	char	*tmp;
	int		j;

	idx->k = -1;
	j = idx->i + 1;
	if (str[j] && str[j] == '?')
		j++;
	else
	{
		while (str[j] && (ft_isalpha(str[j]) == 1 || ft_isalnum(str[j]) == 1
				|| str[j] == '_'))
			j++;
	}
	tmp = fill_tmp(str, idx, j);
	if (tmp != NULL)
	{
		idx->k = -1;
		while (tmp[++idx->k])
			ret[idx->j++] = tmp[idx->k];
		free(tmp);
	}
}

static void	is_d_quotes(char *str, t_index *idx, char *tmp)
{
	idx->i++;
	while (str[idx->i] && str[idx->i] != '"')
	{
		if (str[idx->i] && str[idx->i] != '$')
			tmp[idx->j++] = str[idx->i++];
		else if (str[idx->i] && str[idx->i] == '$' && (str[idx->i + 1] == ' ' || str[idx->i + 1] == '"'))
			tmp[idx->j++] = str[idx->i++];
		else
		{
			var_str(str, idx, tmp);
		}
	}
}

static void	is_s_quotes(char *str, t_index *idx, char *tmp)
{
	idx->i++;
	while (str[idx->i] && str[idx->i] != 39)
		tmp[idx->j++] = str[idx->i++];
	idx->i++;
}

char	*fill_ret(char *str, int i, int j, char *tmp)
{
	t_index	*idx;

	idx = init_idx(i, j, 0, 0);
	while (str[idx->i])
	{
		if (str[idx->i] && str[idx->i] == ' ' && idx->i != 0
			&& str[idx->i - 1] != '"' && str[idx->i - 1] != 39)
			idx->i++;
		else if (str[idx->i] && str[idx->i] == '$'
			&& (str[idx->i + 1] == '"' || str[idx->i + 1] == 39))
			idx->i++;
		else if (str[idx->i] && str[idx->i] == '"')
			is_d_quotes(str, idx, tmp);
		else if (str[idx->i] && str[idx->i] == 39)
			is_s_quotes(str, idx, tmp);
		else
			tmp[idx->j++] = str[idx->i++];
	}
	tmp[idx->j] = '\0';
	free(idx);
	return (tmp);
}
