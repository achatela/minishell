/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:32:45 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/10 13:56:10 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(char *str, int i)
{
	if ((str[i] == '>' && str[i + 1] == '>'))
		return (2);
	else if ((str[i] == '<' && str[i + 1] == '<'))
		return (2);
	else if ((str[i] == '|' && i != 0 && str[i - 1])
		|| (str[i] == '|' && str[i + 1]))
		return (1);
	else if ((str[i] == '<' && i != 0 && str[i - 1])
		|| (str[i] == '<' && str[i + 1]))
		return (1);
	else if ((str[i] == '>' && i != 0 && str[i - 1])
		|| (str[i] == '>' && str[i + 1]))
		return (1);
	return (0);
}

static int	count_args(char **cmds, int i, int j, int k)
{
	while (cmds[++i] != 0)
	{
		j = 0;
		while (cmds[i][j++] != '\0')
		{
			if (is_separator(cmds[i], j) == 2)
			{
				j += 1;
				k++;
			}
			else if (is_separator(cmds[i], j) == 1)
				k++;
			else if (j - 2 > 0 && cmds[i][j]
				&& (is_separator(cmds[i], j - 2) == 2
				|| is_separator(cmds[i], j - 1) == 1))
				k++;
			if (cmds[i][j] == '\0')
				k++;
		}
	}
	return (k);
}

static int	length_word(char *str, int i)
{
	int	ret;

	ret = 0;
	if (is_separator(str, i) == 2)
		return (2);
	if (is_separator(str, i) == 1)
		return(1);
	while (str[i])
	{
//		if (is_separator(str, i) == 2 || is_separator(str, i) == 1)
//			return (ret);
		i++;
		ret++;
	}
	return (ret);
}

static char	**new_array(char **cmds, int i, int j, int k)
{
	char	**new;
	int		l;
	int		m;

	l = 0;
	new = malloc(sizeof(char *) * ((i + j) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (cmds[++i] != 0)
	{
		j = 0;
		while (cmds[i][j])
		{
			k = length_word(cmds[i], j);
			new[l] = malloc(sizeof(char) * (k + 1));
			m = 0;
			while (cmds[i][j] && m < k)
				new[l][m++] = cmds[i][j++];
			new[l++][m] = '\0';
		}
	}
	new[l] = 0;
	return (new);
}

char	**parse_separators(char **cmds, int i)
{
	int		j;
	char	**new;

	j = 0;
	while (cmds[i] != 0)
		i++;
	sep_no_quotes(cmds, i, 0);
	j = count_args(cmds, -1, 0, 0);
	if (j == 0)
		return (cmds);
	new = new_array(cmds, i, j, 0);
	free_cmds(cmds, 0);
	return (new);
}
