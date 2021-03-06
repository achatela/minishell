/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:25:32 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/20 17:55:05 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_heredoc(t_args **args, char *tmp, char **cmds)
{
	while_heredoc((*args), tmp);
	if ((*args)->next != NULL && (*args)->next->next != NULL)
	{
		cmds = new_cmds(cmds, tmp);
		(*args) = new_list((*args), cmds);
	}
	else
		(*args)->to_use = 2;
	free(tmp);
	tmp = get_env_var(g_env, "?", 0);
	if (tmp != NULL && ft_strcmp(tmp, "0") != 0)
	{
		free(tmp);
		free_cmds(cmds, 0);
		return (NULL);
	}
	if (tmp != NULL)
		free(tmp);
	return (cmds);
}
