/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_no_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:47 by achatela          #+#    #+#             */
/*   Updated: 2022/05/16 13:59:24 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	else_no_quotes(char *str, int *i, int *j, int *length)
{
	char	*tmp;
	char	*tmp2;
	int		k;

	k = -1;
	(*j) = (*i);
	while (str[(*j)] && (ft_isalpha(str[(*j)]) == 1
			|| ft_isalnum(str[(*j)]) == 1
			|| str[(*j)] == '_' || str[(*j)] == '-'))
		(*j)++;
	tmp = malloc(sizeof(char) * ((*j) - (*i)) + 2);
	while (++k > -1 && (*i) < (*j))
		tmp[k] = str[(*i)++];
	tmp[k++] = '=';
	tmp[k] = '\0';
	tmp2 = get_env_var(g_env, tmp, 0);
	if (tmp2 != NULL)
	{
		(*length) += ft_strlen(tmp2);
		free(tmp2);
	}
	free(tmp);
}

static int	length_no_quotes(char *str, int i, int j)
{
	int		length;

	length = 0;
	while (str[i])
	{
		if (str[i] != '$')
		{
			i++;
			length++;
		}
		else
		{
			i++;
			if (str[i] == '?' && str[i - 1] == '$')
			{
				length += 2;
				i++;
			}
			else
				else_no_quotes(str, &i, &j, &length);
		}
	}
	return (length + 1);
}

static void	while_no_quotes(char *ret, char *str, t_index *idx)
{
	char	*tmp;
	char	*tmp2;

	idx->j = idx->i;
	while (str[idx->j] && (ft_isalpha(str[idx->j]) == 1
			|| ft_isalnum(str[idx->j]) == 1
			|| str[idx->j] == '_' || str[idx->j] == '-'))
		idx->j++;
	tmp = malloc(sizeof(char) * (idx->j - idx->i) + 2);
	idx->k = -1;
	while (++idx->k > -1 && idx->i < idx->j)
		tmp[idx->k] = str[idx->i++];
	tmp[idx->k++] = '=';
	tmp[idx->k] = '\0';
	idx->k = -1;
	tmp2 = get_env_var(g_env, tmp, 0);
	free(tmp);
	if (tmp2 != NULL)
	{
		while (tmp2[++idx->k])
			ret[idx->l++] = tmp2[idx->k];
		free(tmp2);
	}
}

char	*str_no_quotes(char *str, int i, int j, int k)
{
	char	*ret;
	t_index	*idx;

	idx = init_idx(i, j, k, 0);
	ret = malloc(sizeof(char) * (length_no_quotes(str, 0, 0)) + 1);
	while (str[idx->i])
	{
		if (str[idx->i] && str[idx->i] != '$')
			ret[idx->l++] = str[idx->i++];
		else
		{
			idx->i++;
			if (str[idx->i] == '?' && str[idx->i - 1] == '$')
			{
				ret[idx->l++] = '$';
				ret[idx->l++] = '?';
				idx->i++;
			}
			else
				while_no_quotes(ret, str, idx);
		}
	}
	ret[idx->l] = '\0';
	free(idx);
	return (ret);
}
