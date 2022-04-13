/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:06:50 by cjimenez          #+#    #+#             */
/*   Updated: 2022/04/13 14:12:28 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* EXEC A FAIRE */

int child(char *path, char **cmds)
{
   // char **env_array;
    char *tmp;
    int i;
    int ret;
    pid_t pid;


    ret = 0;
    i = 0;
    pid = fork();
    if (pid == 0)
    {
        /*while (g_env[i] != NULL)
        {
            tmp = g_env[i];
            i++;
        }*/
		i++;
     //   env_array = ft_split(tmp, '\n');
     //   ft_memdel(tmp);
	 	tmp = ft_strchr(path, '/');
        if (tmp != NULL)
            execve(path, cmds, g_env);
        ret = 1;
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
    DIR *folder;
    struct dirent *dir;
    char *path;

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
//	free(dir);
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
	(void)command_not_found;
    while (g_env[i] && ft_strncmp(g_env[i], "PATH=", 5))
        i++;
    if (g_env[i] == 0)
        return (1);
    bin = ft_split(g_env[i], ':');
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
    	i = child(path, cmds);
	else
	{
		tmp = command_not_found(args, -1, "command-not-found");
		child("/usr/lib/command-not-found", tmp);
		free(bin[j]);
	}
//	UTILISER /usr/lib/command-not-found
//	QUAND LA COMMAND EST NOT FOUND
	free(bin);
	free(path);
	return (i);
}
