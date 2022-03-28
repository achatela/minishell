/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:15:02 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 16:21:14 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		a;
	t_list	*head;

	head = lst;
	a = 0;
	while (head != NULL)
	{
		a++;
		head = head->next;
	}
	return (a);
}
