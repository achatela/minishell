/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:18:45 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 17:33:05 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		a;
	char		*dst;
	const char	*source;

	if (dest == NULL && src == NULL && n > 0)
		return (NULL);
	a = 0;
	source = src;
	dst = dest;
	while (a < n)
	{
		dst[a] = source[a];
		a++;
	}
	return (dest);
}
