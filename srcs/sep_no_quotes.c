/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_no_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:45:39 by achatela          #+#    #+#             */
/*   Updated: 2022/05/14 17:32:27 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_cmds_length(char **cmds, int i, int j, int k)
{
	while (cmds[i])
	{
		j = 0;
		if (cmds[i][j] == 39 && cmds[i][j] == '"')
			i++;
		else
		{
			while (cmds[i][j])
			{
				if ((cmds[i][j] == '>' && cmds[i][j + 1] == '>')
					|| (cmds[i][j] == '<' && cmds[i][j + 1] == '<'))
					cmds_length(cmds, &i, &j, &k);
				else if (cmds[i][j] && (cmds[i][j] == '<' || cmds[i][j] == '>'))
					cmds_length2(cmds, &i, &j, &k);
				else
					j++;
			}
			i++;
		}
	}
	return (k + 1);
}

char	*new_string(char **cmds, int i, int j, int k)
{
	char	*str;

	while (cmds[i][j] && (cmds[i][j] != '<' && cmds[i][j] != '>'))
		j++;
	str = malloc(sizeof(char) * (j - (k - 1)));
	if (!str)
		return (NULL);
	j = 0;
	while (cmds[i][k] && cmds[i][k] != '<' && cmds[i][k] != '>')
		str[j++] = cmds[i][k++];
	str[j] = '\0';
	return (str);
}

char	*new_separator(char **cmds, int i, int j, int k)
{
	char	*str;

	while (cmds[i][j] || cmds[i][j] == '<' || cmds[i][j] == '>')
		j++;
	str = malloc(sizeof(char) * (j - (k - 1)));
	if (!str)
		return (NULL);
	j = 0;
	while (cmds[i][k] && (cmds[i][k] == '<' || cmds[i][k] == '>'))
		str[j++] = cmds[i][k++];
	str[j] = '\0';
	return (str);
}

static char	**new_separated(char **cmds, int i, int j, char	**new)
{
	int	k;

	k = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i] != 0 && cmds[i][j])
		{
			if (cmds[i] != 0 && cmds[i][j]
				&& (cmds[i][j] == '"' || cmds[i][j] == 39))
			{
				new[k++] = ft_strdup(cmds[i]);
				break ;
			}
			else if (cmds[i] != 0 && cmds[i][j]
				&& cmds[i][j] != '<' && cmds[i][j] != '>')
				new[k++] = new_is_string(cmds, &j, i);
			else if (cmds[i] != 0 && cmds[i][j]
				&& (cmds[i][j] == '<' || cmds[i][j] == '>'))
				new[k++] = new_is_sep(cmds, &j, i);
		}
		i++;
	}
	new[k] = 0;
	return (new);
}

char	**sep_no_quotes(char **cmds, int i, int j)
{
	char	**new;

	j = new_cmds_length(cmds, 0, 0, 0);
	if (j <= 1)
		return (cmds);
	else
	{
		new = malloc(sizeof(char *) * (i + j));
		if (!new)
			return (NULL);
		new = new_separated(cmds, 0, 0, new);
		free_cmds(cmds, 0);
	}
	return (new);
}
