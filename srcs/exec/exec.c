/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:06:50 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/07 14:56:06 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* EXEC A FAIRE */

static int isseparator(char *str, int i)
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
	int		k;
	char	**new;

	k = 0;
	if (ft_strcmp(cmds[0], "command-not-found") == 0)
		i = -1;
	while (path[k])
		k++;
	while (path[k - 1] != '/')
		k--;
	while (cmds[++i] != 0)
	{
		if (ft_strncmp(cmds[i], path + k, ft_strlen(path + k)) == 0)
			break;
	}
	j = i;
	if (cmds[i] == 0)
		return (cmds);
	else if (cmds[i + 1] == 0)
	{
		new = malloc(sizeof(char *) * 2);
		new[0] = cmds[i];
		new[1] = 0;
		return (new);
	}
	else if (cmds[i] != 0)
	{
		k = 0;
		while(cmds[i] != 0 && isseparator(cmds[i], 0) == 0)
		{
			k++;
			i++;
		}
		new = malloc(sizeof(char *) * (k + 2));
		k = 0;
		while (cmds[j] != 0 && isseparator(cmds[j], 0) == 0)
		{
			i = -1;
			new[k] = malloc(sizeof(char) * ft_strlen(cmds[j]) + 1);
			while (cmds[j][++i])
				new[k][i] = cmds[j][i];
			new[k++][i] = '\0';
			j++;
		}
		new[k] = 0;
	}
	return (new);
}

int child(char *path, char **cmds, t_args *args)
{
   // char **env_array;
    char	*tmp;
    char	**new;
    int		ret;
    pid_t	pid;


    ret = 0;
    pid = fork();
    if (pid == 0)
    {
        /*while (g_env[i] != NULL)
        {
            tmp = g_env[i];
            i++;
        }*/
     //   env_array = ft_split(tmp, '\n');
     //   ft_memdel(tmp);
	 	new = args_exec(cmds, path, args->index - 1, 0);
	 	tmp = ft_strchr(path, '/');
        if (tmp != NULL)
            execve(path, new, g_env);
        ret = 1;
		free_cmds(new, 0);
		free(tmp);
        exit(ret);
    }
    else
        waitpid(pid, &ret, 0);
    return (ret);
}


char    *path_join(const char *s1, const char *s2)
{
    char *tmp;
    char *path;

    tmp = ft_strjoin(s1, "/");
    path = ft_strjoin(tmp, s2);
//  ft_memdel(tmp);
    return (path);
}

char *check_dir(char *bin, char *cmd)
{
    DIR		*folder;
    struct	dirent *dir;
    char	*path;
	int		i;

	i = 0;
	while (cmd[i] != '\0')
		i++;
	while (i != 0 && cmd[i] != '/')
		i--;
	if (i == 0 || cmd[i] == '/')
	{
		if (cmd[i] == '/')
		{
			i++;
			while (i-- != 0)
				cmd++;
		}
	}
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

static char	**command_not_found(t_args *args, int i, char *str)
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
/*	if (args->next != NULL)
	{
		new[0] = malloc(sizeof(char) * ft_strlen(args->next->parsed_arg) + 1);
		while (args->next->parsed_arg[++i])
			new[0][i] = args->next->parsed_arg[i];
		new[0][i] = '\0';
		i = -1;
		new[1] = malloc(sizeof(char) * ft_strlen(args->parsed_arg) + 1);
		while (args->parsed_arg[++i])
			new[1][i] = args->parsed_arg[i];
		new[1][i] = '\0';
	}*/
	return (new);
}

int exec_bin(char **cmds, t_args *args)
{
    int     i;
    char    **bin;
    char    *path;
	int		j;
	char	**tmp;

    i = 0;
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
	{
        path = check_dir(bin[i++], args->parsed_arg);
	}
	j = i - 1;
	i = -1;
	while (bin[++i] != 0)
	{
		if (bin[i] != NULL && i != j)
			free(bin[i]);
	}
	i = 0;
	if (path != NULL)
    	i = child(path, cmds, args);
	else
	{
		tmp = command_not_found(args, -1, "command-not-found");
		child("/usr/lib/command-not-found", tmp, args);
		free_cmds(tmp, 0);
		free(bin[j]);
	}
//	UTILISER /usr/lib/command-not-found
//	QUAND LA COMMAND EST NOT FOUND
	free(bin);
	free(path);
	return (i);
}
