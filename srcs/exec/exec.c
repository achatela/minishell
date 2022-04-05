/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:06:50 by cjimenez          #+#    #+#             */
/*   Updated: 2022/04/04 17:52:06 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* EXEC A FAIRE */

int child(char *path, char **args)
{
    char **env_array;
    char *tmp;
    int ret;
    pid_t pid;

    ret = 0;
    pid = fork();
    if (pid == 0)
    {
        tmp = 
    }
}

char    *path_join(const char *s1, const char *s2)
{
    char *tmp;
    char *path;

    tmp = ft_strjoin(s1, "/");
    path = ft_strjoin(tmp, s2);
    ft_memdel(tmp);
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
    return (path);

}

int exec_bin(char **args)
{
    int     i;
    char    **bin;
    char    *path;
    int     ret;

    i = 0;
    ret = 0;
    while (g_env[i] && ft_strncmp(g_env[i], "PATH=", 5))
        i++;
    if (g_env[i] == NULL)
        return (1);
    bin = ft_split(g_env[i], ':');
    if (!args[0] && !bin[0])
        return (1);
    path = check_dir(bin[0] + 5, args[0]);
    i = 1;
    while (args[0] && bin[i] && path == NULL)
        path = check_dir(bin[i++], args[0]);
    ret = path;
    return (ret);
}
