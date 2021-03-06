/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:13:54 by achatela          #+#    #+#             */
/*   Updated: 2022/04/06 14:39:23 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	int	a;

	a = 0;
	while (s[a] && s[a] != ' ')
	{
		if (s[a] == (char)c)
			return ((char *)s + a);
		a++;
	}
	if (s[a] == (char)c)
		return ((char *)s + a);
	return (NULL);
}
