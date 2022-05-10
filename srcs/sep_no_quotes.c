/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_no_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:45:39 by achatela          #+#    #+#             */
/*   Updated: 2022/05/10 14:33:07 by achatela         ###   ########.fr       */
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
					j += 2;
					k += 2;
				}
				else if (cmds[i][j] == '<' || cmds[i][j] == '>')
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

char	**sep_no_quotes(char **cmds, int i, int j)
{
	char	**new;

	j = new_cmds_length(cmds, 0, 0, 0);
	if (j <= 1)
		return (cmds);
	else
	{
		new = malloc(sizeof(char *) * (i + j + 1));
		(void)new;
		printf("%d\n", (i + j));
		return (cmds);
	}
	return (cmds);
}
