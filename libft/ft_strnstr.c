/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:35:17 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 13:45:12 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;
	size_t	b;
	size_t	c;

	if (!little[0])
		return ((char *)big);
	a = 0;
	while (a < len && big[a])
	{
		b = 0;
		if (big[a] == little[b])
		{
			c = a;
			while (big[a] == little[b] && a < len)
			{
				a++;
				b++;
				if (little[b] == '\0')
					return ((char *)big + c);
			}
			a = c;
		}
		a++;
	}
	return (NULL);
}
