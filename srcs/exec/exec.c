/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:56:57 by achatela          #+#    #+#             */
/*   Updated: 2022/06/20 16:59:00 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_to_exec(char *pwd, t_args *args)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = args->parsed_arg;
	if (tmp && (tmp[0] == '.' || tmp[0] == '/'))
	{
		tmp++;
		ret = ft_strjoin(pwd, tmp);
	}
	else
	{
		ret = ft_strjoin(pwd, "/");
		ret = ft_strjoin(ret, tmp);
	}
	return (ret);
}

static int	exec_bash(t_pipe exec, t_args *args)
{
	char	*path;
	int		i;

	path = get_path_to_exec(getcwd(NULL, 0), args);
	if (access(path, X_OK) == -1)
	{
		free(path);
		return (-1);
	}
	else
	{
		i = child(path, exec.cmds, args);
		free(path);
		return (i);
	}
}

int	exec_bin_check(t_pipe exec, t_args *args, int i, char **bin)
{
	char	*path;

	if (!args->parsed_arg && !bin[0])
		return (1);
	path = check_dir(bin[0], args->parsed_arg);
	i = 1;
	while (args->parsed_arg && bin[i] && path == NULL)
		path = check_dir(bin[i++], args->parsed_arg);
	exec_bin_end(bin, path, i, exec);
	return (i);
}

int	exec_bin(char **cmds, t_args *args, int i)
{
	char	**bin;
	t_pipe	exec;

	exec.cmds = cmds;
	exec.args = args;
	if (exec_bash(exec, args) != -1)
		return (1);
	if (check_unset_path(i, args->parsed_arg) == 1)
		return (i);
	while (g_env[i] && ft_strncmp(g_env[i], "PATH=", 5))
		i++;
	if (g_env[i] == 0 && getenv("PATH") != NULL)
		bin = ft_split(getenv("PATH"), ':');
	else if (g_env[i] != 0)
		bin = ft_split(g_env[i], ':');
	else
		return (printf("%s: PATH not set\n", args->parsed_arg), 1);
	exec_bin_check(exec, args, i, bin);
	return (i);
}
