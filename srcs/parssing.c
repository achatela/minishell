/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:50:20 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/08 16:51:34 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	while_sep(t_args *args, char **cmds)
{
	int		i;
	t_args	*head;

	i = 0;
	head = args;
	while (args)
	{
		while (args && (args->is_separator == 0 || args->is_separator == 1)
			&& i == 0)
			args = while_send_sep(args, &i, head, cmds);
		i = 0;
		if (args && args->is_separator == 0)
			args = skip_cmd(args);
		while (args && args->is_separator == 2)
			args = args->next;
		head = args;
	}
}
