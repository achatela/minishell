/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:00:52 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 17:40:41 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			a;
	unsigned char	*buff;

	a = 0;
	buff = (unsigned char *)s;
	if (n == 0)
		return (s);
	while (a < n)
	{
		buff[a] = (unsigned char)c;
		a++;
	}
	return (s);
}
