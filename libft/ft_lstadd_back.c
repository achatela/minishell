/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:25:45 by achatela          #+#    #+#             */
/*   Updated: 2022/04/01 15:21:34 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_args *alst, t_args *new)
{
	t_args	*head;

	if (!alst)
		alst = new;
	if (alst)
	{
		head = alst;
		while (head->next != NULL)
			head = head->next;
		head->next = new;
	}
}
