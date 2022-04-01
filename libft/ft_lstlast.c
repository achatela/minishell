/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:21:37 by achatela          #+#    #+#             */
/*   Updated: 2022/04/01 15:11:11 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_args	*ft_lstlast(t_args *lst)
{
	t_args	*head;

	head = lst;
	if (head)
	{	
		while (head->next != NULL)
			head = head->next;
	}
	return (head);
}
