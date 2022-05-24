/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:53:29 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/24 15:00:34 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_double_redir(char **cmds, t_args *args, t_args *head)
{
	printf("syntax error near unexepected token ");
	printf("`%s'\n", args->next->parsed_arg);
	free_cmds(cmds, 0);
	free_list(head);
	return (-1);
}
