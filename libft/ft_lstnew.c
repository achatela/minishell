/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:43:32 by achatela          #+#    #+#             */
/*   Updated: 2022/04/01 15:20:57 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_args	*ft_lstnew(void *content)
{
	t_args	*new;

	new = malloc(sizeof(t_args) * 1);
	(void)content;
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}
