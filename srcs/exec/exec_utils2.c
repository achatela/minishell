/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:38:28 by achatela          #+#    #+#             */
/*   Updated: 2022/05/16 17:52:35 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**args_exec_not_end(char **cmds, t_index *idx)
{
	char	**new;

	idx->k = 0;
	while (cmds[idx->i] != 0 && isseparator(cmds[idx->i], 0) == 0)
	{
		idx->k++;
		idx->i++;
	}
	new = malloc(sizeof(char *) * (idx->k + 2));
	idx->k = 0;
	while (cmds[idx->j] != 0 && isseparator(cmds[idx->j], 0) == 0)
	{
		idx->i = -1;
		new[idx->k] = malloc(sizeof(char) * ft_strlen(cmds[idx->j]) + 1);
		while (cmds[idx->j][++idx->i])
			new[idx->k][idx->i] = cmds[idx->j][idx->i];
		new[idx->k++][idx->i] = '\0';
		idx->j++;
	}
	new[idx->k] = 0;
	free(idx);
	return (new);
}
