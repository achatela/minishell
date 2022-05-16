/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:31:17 by achatela          #+#    #+#             */
/*   Updated: 2022/05/16 17:38:39 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_ret_value(t_args *args, int ret)
{
	if (WIFEXITED(ret))
		args->echo->print = WEXITSTATUS(ret);
	if (WIFSIGNALED(ret))
	{
		args->echo->print = WTERMSIG(ret);
		if (args->echo->print != 131)
			args->echo->print += 128;
	}
}

void	get_cmd_char(int *i, char *cmd)
{
	while (cmd[(*i)] != '\0')
		(*i)++;
	while ((*i) != 0 && cmd[(*i)] != '/')
		(*i)--;
	if ((*i) == 0 || cmd[(*i)] == '/')
	{
		if (cmd[(*i)] == '/')
		{
			(*i)++;
			while ((*i)-- != 0)
				cmd++;
		}
	}
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	return (path);
}

char	*check_dir(char *bin, char *cmd)
{
	DIR				*folder;
	struct dirent	*dir;
	char			*path;
	int				i;

	i = 0;
	get_cmd_char(&i, cmd);
	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	dir = readdir(folder);
	while (dir != NULL)
	{
		if (dir == NULL)
			break ;
		if (ft_strcmp(dir->d_name, cmd) == 0)
			path = path_join(bin, dir->d_name);
		dir = readdir(folder);
	}
	closedir(folder);
	return (path);
}

void	check_path(char **cmds, t_index *idx, char *path)
{
	if (ft_strcmp(cmds[0], "command-not-found") == 0)
		idx->i = -1;
	while (path[idx->k])
		idx->k++;
	while (path[(idx->k - 1)] != '/')
		idx->k--;
	while (cmds[++idx->i] != 0)
	{
		if (ft_strncmp(cmds[idx->i], path + idx->k,
				ft_strlen(path + idx->k)) == 0)
			break ;
	}
	idx->j = idx->i;
}
