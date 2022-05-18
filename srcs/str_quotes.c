/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:57 by achatela          #+#    #+#             */
/*   Updated: 2022/05/18 17:13:57 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_length(char *str, int i, int j, int k)
{
	char	*tmp;
	char	*tmp2;
	int		length;

	length = 0;
	j = i + 1;
	if (str[j] && str[j] == '?')
		j++;
	else
	{
		while (str[j] && (ft_isalpha(str[j]) == 1 || ft_isalnum(str[j]) == 1
				|| str[j] == '_'))
			j++;
	}
	tmp = malloc(sizeof(char) * (j - i) + 2);
	i++;
	while (++k > -1 && i < j)
		tmp[k] = str[i++];
	tmp[k++] = '=';
	tmp[k] = '\0';
	tmp2 = get_env_var(g_env, tmp, 0);
	if (tmp2 == NULL)
	{
		tmp2 = malloc(sizeof(char));
		tmp2[0] = '\0';
	}
	length += ft_strlen(tmp2);
	free(tmp);
	free(tmp2);
	return (length);
}

static int	length_d_quotes(char *str, int *i, int length)
{
	(*i)++;
	while (str[(*i)] && str[(*i)] != '"')
	{
		if (str[(*i)] && str[(*i)] == '$')
		{
			length += var_length(str, (*i), (*i) + 1, -1);
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
		else
		{
			(*i)++;
			length++;
		}
	}
	if (str[(*i)])
		(*i)++;
	return (length);
}

static int	length_s_quotes(char *str, int *i, int length)
{
	(*i)++;
	while (str[(*i)] && str[(*i)] != 39)
	{
		length++;
		(*i)++;
	}
	(*i)++;
	return (length);
}

static int	length_quotes(char *str, int i, int length)
{
	while (str[i])
	{
		if (str[i] && str[i] == '"')
			length = length_d_quotes(str, &i, length);
		else if (str[i] && str[i] == 39)
			length = length_s_quotes(str, &i, length);
		else
		{
			i++;
			length++;
		}
	}
	return (length);
}

char	*str_quotes(char *str)
{
	char	*ret;

	if (str[0] == '\0' || str[0] == 32)
		return (NULL);
	ret = malloc(sizeof(char) * (length_quotes(str, 0, 0) + 1));
	ret = fill_ret(str, 0, 0, ret);
	return (ret);
}
