/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:59:16 by achatela          #+#    #+#             */
/*   Updated: 2022/05/14 16:59:38 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_sep(t_args *args)
{
	t_args	*head;

	head = args;
	while (head && head->next)
	{
		if (head->is_separator == 1)
			return (1);
		head = head->next;
	}
	if (head->is_separator == 1)
		return (1);
	return (0);
}
