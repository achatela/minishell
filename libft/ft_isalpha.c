/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:06:27 by achatela          #+#    #+#             */
/*   Updated: 2021/11/25 13:06:54 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalpha(int c)
{
	int	a;

	a = 0;
	if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97))
		a = 1;
	else
		a = 0;
	return (a);
}
