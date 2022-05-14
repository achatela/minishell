/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_no_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:05:47 by achatela          #+#    #+#             */
/*   Updated: 2022/05/14 18:35:11 by achatela         ###   ########.fr       */
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

//static char	*while_no_quotes(char *ret, char *str, 

char	*str_no_quotes(char *str, int i, int j, int k)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	int		l;

	l = 0;
	ret = malloc(sizeof(char) * (length_no_quotes(str, 0, 0)) + 1);
	tmp = ret;
	while (str[i])
	{
		if (str[i] && str[i] != '$')
			ret[l++] = str[i++];
		else
		{
			i++;
			if (str[i] == '?' && str[i - 1] == '$')
			{
				ret[l++] = '$';
				ret[l++] = '?';
				i++;
			}
			else
			{
				j = i;
				while (str[j] && (ft_isalpha(str[j]) == 1
						|| ft_isalnum(str[j]) == 1
						|| str[j] == '_' || str[j] == '-'))
					j++;
				tmp = malloc(sizeof(char) * (j - i) + 2);
				k = -1;
				while (++k > -1 && i < j)
					tmp[k] = str[i++];
				tmp[k++] = '=';
				tmp[k] = '\0';
				k = -1;
				tmp2 = get_env_var(g_env, tmp, 0);
				free(tmp);
				if (tmp2 != NULL)
				{
					while (tmp2[++k])
						ret[l++] = tmp2[k];
					free(tmp2);
				}
			}
		}
	}
	ret[l] = '\0';
	return (tmp);
}
