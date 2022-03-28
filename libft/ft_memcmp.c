/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:42:29 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 17:10:04 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				a;
	unsigned const char	*source1;
	unsigned const char	*source2;

	source1 = s1;
	source2 = s2;
	a = 0;
	if (n == 0)
		return (0);
	while (a < n)
	{
		if (a == n - 1 && source1[a] == source2[a])
			return (0);
		if (source1[a] != source2[a])
			return (source1[a] - source2[a]);
		a++;
	}
	return (source1[a] - source2[a]);
}
