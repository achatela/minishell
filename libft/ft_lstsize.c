/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:15:02 by achatela          #+#    #+#             */
/*   Updated: 2022/04/01 15:17:13 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_args *lst)
{
	int		a;
	t_args	*head;

	head = lst;
	a = 0;
	while (head != NULL)
	{
		a++;
		head = head->next;
	}
	return (a);
}
