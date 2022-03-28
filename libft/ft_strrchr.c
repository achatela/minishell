/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:22:30 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 13:45:32 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	a;

	a = 0;
	while (s[a])
		a++;
	if (s[a] == (char)c)
		return ((char *)s + a);
	while (a > -1)
	{
		a--;
		if (s[a + 1] == (char)c)
			return ((char *)s + a + 1);
	}
	return (NULL);
}
