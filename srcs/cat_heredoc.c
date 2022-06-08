/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:42:01 by achatela          #+#    #+#             */
/*   Updated: 2022/06/08 17:17:42 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**cat_cmds(t_args *cat)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * 3);
	tmp[0] = ft_strdup(cat->parsed_arg);
	tmp[1] = ft_strdup(cat->next->parsed_arg);
	tmp[2] = 0;
	return (tmp);
}

static void	rm_tmpfile(t_args *rm, char *tmpfile)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * 3);
	tmp[0] = ft_strdup("rm");
	tmp[1] = ft_strdup(tmpfile);
	tmp[2] = 0;
	send_builtin(rm, tmp);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
}

static void	free_catheredoc(t_args *cat, t_args *rm, char **cmds)
{
	free(rm->next->parsed_arg);
	free(rm->next);
	free(rm->parsed_arg);
	free(rm);
	free(cat->next->parsed_arg);
	free(cat->next);
	free(cat->parsed_arg);
	free(cat);
	free(cmds[0]);
	free(cmds[1]);
	free(cmds);
}

static void	cat_end(void)
{
	t_args	*cat;
	t_args	*rm;
	char	**cmds;

	cat = ft_lstnew(NULL);
	cat->parsed_arg = ft_strdup("cat");
	cat->next = ft_lstnew(NULL);
	cat->next->parsed_arg = ft_strdup("tmpfilecatheredoc");
	cmds = cat_cmds(cat);
	send_builtin(cat, cmds);
	rm = ft_lstnew(NULL);
	rm->next = ft_lstnew(NULL);
	rm->parsed_arg = ft_strdup("rm");
	rm->next->parsed_arg = ft_strdup("tmpfilecatheredoc");
	rm_tmpfile(rm, "tmpfilecatheredoc");
	free_catheredoc(cat, rm, cmds);
}

void	cat_here_doc(t_args *args, int i, int fd, char *delimiter)
{
	delimiter = get_delimiter(delimiter, args);
	fd = open("tmpfilecatheredoc", O_WRONLY | O_APPEND | O_CREAT, 0644);
	cat_here_doc2(i, fd, delimiter);
	cat_end();
}
