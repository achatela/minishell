/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:36:13 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 13:40:48 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				a;
	const unsigned char	*source;

	a = 0;
	if (n == 0)
		return (NULL);
	source = s;
	while (a < n)
	{
		if (source[a] == (unsigned char)c)
			return ((void *)s + a);
		a++;
	}
	return (NULL);
}
