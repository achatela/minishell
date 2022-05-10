/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_no_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:45:39 by achatela          #+#    #+#             */
/*   Updated: 2022/05/10 16:35:24 by achatela         ###   ########.fr       */
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
				{
					if (j != 0 && (cmds[i][j - 1] == '>' || cmds[i][j - 1] == '<'))
						k++;
					else
						k += 2;
					j += 2;
				}
				else if (cmds[i][j] && (cmds[i][j] == '<' || cmds[i][j] == '>'))
				{
					if (j != 0 && (cmds[i][j - 1] == '>' || cmds[i][j - 1] == '<'))
						k++;
					else
						k += 2;
					j++;
				}
				else
					j++;
			}
			i++;
		}
	}
	return (k + 1);
}

static char	*new_string(char **cmds, int i, int j, int k)
{
	char	*str;

	while (cmds[i][j] && (cmds[i][j] != '<' && cmds[i][j] != '>'))
		j++;
	printf("%d\n", (j - (k - 1)));
	str = malloc(sizeof(char) * (j - (k - 1)));
	if (!str)
		return (NULL);
	j = 0;
	while (cmds[i][k] && cmds[i][k] != '<' && cmds[i][k] != '>')
		str[j++] = cmds[i][k++];
	str[j] = '\0';
	return (str);
}

static char *new_separator(char **cmds, int i, int j, int k)
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
		while (cmds[i][j])
		{
			if (cmds[i][j] != '<' && cmds[i][j] != '>')
			{
				new[k++] = new_string(cmds, i, j, j);
				while (cmds[i][j] && cmds[i][j] != '<' && cmds[i][j] != '>')
					j++;
			}
			else if (cmds[i][j] == '<' || cmds[i][j] == '>')
			{
				new[k++] = new_separator(cmds, i, j, j);
				while (cmds[i][j] && (cmds[i][j] == '>' || cmds[i][j] == '<'))
					j++;
			}
		}
		i++;
	}
	new[k] = 0;
	free_cmds(cmds, 0);
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
	}
	return (new);
}