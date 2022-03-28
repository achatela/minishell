/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:55:28 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 17:19:43 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;
	size_t		a;

	if (dest == NULL && src == NULL)
		return (NULL);
	a = 0;
	s = src;
	d = dest;
	if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	else
	{
		while (a < n)
		{
			d[a] = s[a];
			a++;
		}
	}
	return (dest);
}
