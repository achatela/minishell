/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:55:05 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/08 17:03:06 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cat_here_doc2(int i, int fd, char *delimiter)
{
	static int	line = 1;
	char		*tmp;

	while (i != 1)
	{
		tmp = readline("> ");
		if (tmp == NULL)
		{
			printf("warning: here-document at line %d ", line++);
			printf("delimited by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		else if (ft_strcmp(tmp, delimiter) == 0)
			i = 1;
		if (ft_strcmp(tmp, delimiter) != 0)
		{
			write(fd, tmp, ft_strlen(tmp));
			write(fd, "\n", 2);
		}
		free(tmp);
		line++;
	}
	line = 1;
}
