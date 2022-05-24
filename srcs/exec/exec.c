/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:56:57 by achatela          #+#    #+#             */
/*   Updated: 2022/05/24 14:42:25 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isseparator(char *str, int i)
{
	if (str[i] == '|')
		return (1);
	if (str[i] == '<')
		return (1);
	if (str[i] == '>')
		return (1);
	return (0);
}

static char	**args_exec(char **cmds, char *path, int i, int j)
{
	char	**new;
	t_index	*idx;

	idx = init_idx(i, j, 0, 0);
	if (cmds[0] == 0)
	{
		free(idx);
		return (NULL);
	}
	check_path(cmds, idx, path);
	if (cmds[idx->i] == 0)
	{
		free(idx);
		return (cmds);
	}
	else if (cmds[idx->i + 1] == 0)
	{
		new = malloc(sizeof(char *) * 2);
		new[0] = cmds[idx->i];
		new[1] = 0;
		free(idx);
	}
	else if (cmds[idx->i] != 0)
		new = args_exec_not_end(cmds, idx);
	return (new);
}

int	child(char *path, char **cmds, t_args *args)
{
	char	*tmp;
	char	**new;
	int		ret;
	pid_t	pid;

	ret = 0;
	pid = fork();
	builtin_export(g_env, ft_export(0, "export"));
	if (pid == 0)
	{
		new = args_exec(cmds, path, args->index - 1, 0);
		if (new == NULL)
			exit(ret);
		tmp = ft_strchr(path, '/');
		if (tmp != NULL)
			execve(path, new, g_env);
		free_cmds(new, 0);
		free(tmp);
		exit(ret);
	}
	else
		waitpid(pid, &ret, 0);
	get_ret_value(args, ret);
	return (ret);
}

char	**command_not_found(t_args *args, int i, char *str)
{
	char	**new;

	new = malloc(sizeof(char *) * 3);
	if (!new)
		return (NULL);
	new[0] = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[++i])
		new[0][i] = str[i];
	new[0][i] = '\0';
	i = -1;
	new[1] = malloc(sizeof(char) * ft_strlen(args->parsed_arg) + 1);
	while (args->parsed_arg[++i])
		new[1][i] = args->parsed_arg[i];
	new[1][i] = '\0';
	new[2] = 0;
	return (new);
}

int	exec_bin(char **cmds, t_args *args, int i)
{
	char	**bin;
	char	*path;
	t_pipe	exec;

	if (check_unset_path(i, args->parsed_arg) == 1)
		return (i);
	exec.cmds = cmds;
	exec.args = args;
	while (g_env[i] && ft_strncmp(g_env[i], "PATH=", 5))
		i++;
	if (g_env[i] == 0 && getenv("PATH") != NULL)
		bin = ft_split(getenv("PATH"), ':');
	else if (g_env[i] != 0)
		bin = ft_split(g_env[i], ':');
	else
		return (printf("%s: PATH not set\n", args->parsed_arg), 1);
	if (!args->parsed_arg && !bin[0])
		return (1);
	path = check_dir(bin[0], args->parsed_arg);
	i = 1;
	while (args->parsed_arg && bin[i] && path == NULL)
		path = check_dir(bin[i++], args->parsed_arg);
	exec_bin_end(bin, path, i, exec);
	return (i);
}
