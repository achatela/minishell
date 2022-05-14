/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_quotes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:09:44 by achatela          #+#    #+#             */
/*   Updated: 2022/05/14 18:26:11 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_str(char *str, int i, int j, int k)
{
	char	*tmp;
	char	*ret;

	while (str[j] && (ft_isalpha(str[j]) == 1 || ft_isalnum(str[j]) == 1
			|| str[j] == '_'))
		j++;
	tmp = malloc(sizeof(char) * ((j - i) + 2));
	i++;
	while (++k > -1 && i < j)
		tmp[k] = str[i++];
	tmp[k++] = '=';
	tmp[k] = '\0';
	ret = get_env_var(g_env, tmp, 0);
	free(tmp);
	return (ret);
}

static void	is_d_quotes(char *str, int *i, int *j, char *tmp)
{
	char	*tmp2;
	char	*free_tmp2;

	(*i)++;
	while (str[(*i)] && str[(*i)] != '"')
	{
		if (str[(*i)] && str[(*i)] == '$')
		{
			tmp2 = var_str(str, (*i), (*i) + 1, -1);
			free_tmp2 = tmp2;
			if (tmp2 != NULL)
			{
				while ((*tmp2))
					tmp[(*j)++] = *tmp2++;
			}
			(*i)++;
			while (str[(*i)] && (ft_isalpha(str[(*i)]) == 1
					|| ft_isalnum(str[(*i)]) == 1
					|| str[(*i)] == '_'))
				(*i)++;
			free(free_tmp2);
		}
		else
			tmp[(*j)++] = str[(*i)++];
	}
}

static void	is_s_quotes(char *str, int *i, int *j, char *tmp)
{
	(*i)++;
	while (str[(*i)] && str[(*i)] != 39)
		tmp[(*j)++] = str[(*i)++];
	(*i)++;
}

static void	is_dollar(char *str, int *i, int *j, char *tmp)
{
	char	*tmp2;
	char	*free_tmp2;

	if (str[(*i)] && str[(*i)] == '$')
	{
		tmp2 = var_str(str, (*i), (*i) + 1, -1);
		free_tmp2 = tmp2;
		if (tmp2 != NULL)
		{
			while ((*tmp2))
				tmp[(*j)] = *tmp2++;
		}
		(*i)++;
		while (str[(*i)] && (ft_isalpha(str[*(i)]) == 1
				|| ft_isalnum(str[(*i)]) == 1 || str[(*i)] == '_'))
			(*i)++;
		free(free_tmp2);
	}
}

char	*fill_ret(char *str, int i, int j, char *tmp)
{
	while (str[i])
	{
		if (str[i] && str[i] == ' ' && i != 0
			&& str[i - 1] != '"' && str[i - 1] != 39)
			i++;
		else if (str[i] && str[i] == '$'
			&& (str[i + 1] == '"' || str[i + 1] == 39))
			i++;
		else if (str[i] && str[i] == '"')
			is_d_quotes(str, &i, &j, tmp);
		else if (str[i] && str[i] == 39)
			is_s_quotes(str, &i, &j, tmp);
		else if (str[i] && str[i] == '$')
			is_dollar(str, &i, &j, tmp);
		else
			tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}
