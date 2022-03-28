/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:27:40 by achatela          #+#    #+#             */
/*   Updated: 2021/11/30 20:09:11 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	b;
	size_t	c;

	a = 0;
	b = ft_strlen(dst);
	c = ft_strlen(src);
	if (size <= b)
		return (c + size);
	if (a == size)
		return (size);
	while (src[a] && (b + a) < size - 1)
	{
		dst[b + a] = src[a];
		a++;
	}
	dst[b + a] = '\0';
	return (b + c);
}
