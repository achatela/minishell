/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:38:28 by achatela          #+#    #+#             */
/*   Updated: 2022/06/06 18:14:42 by cjimenez         ###   ########.fr       */
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

void	exec_bin_end(char **bin, char *path, int i, t_pipe exec)
{
	int		j;
	char	**tmp;

	j = i - 1;
	i = -1;
	while (bin[++i] != 0)
	{
		if (bin[i] != NULL && i != j)
			free(bin[i]);
	}
	i = 0;
	if (path != NULL)
		i = child(path, exec.cmds, exec.args);
	else
	{
		tmp = command_not_found(exec.args, -1, "command-not-found");
		child("/usr/lib/command-not-found", tmp, exec.args);
		free_cmds(tmp, 0);
		free(bin[j]);
	}
	free(bin);
	free(path);
}

int	check_unset_path(int i, char *cmd)
{
	char	*tmp;

	if (cmd && cmd[0] == '/')
		return (0);
	tmp = get_env_var(g_env, "PATH", i);
	if (tmp == NULL)
	{
		printf("%s: No such file or directory\n", cmd);
		return (1);
	}
	else
	{
		free(tmp);
		return (0);
	}
}
