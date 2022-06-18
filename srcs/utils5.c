/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:30:46 by achatela          #+#    #+#             */
/*   Updated: 2022/06/18 16:40:45 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	*init_pips(int i)
{
	t_fd	*ret;

	ret = malloc(sizeof(t_fd));
	ret->i = i;
	ret->tmpin = dup(STDIN_FILENO);
	ret->tmpout = dup(STDOUT_FILENO);
	return (ret);
}
