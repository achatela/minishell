/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:44:39 by achatela          #+#    #+#             */
/*   Updated: 2021/11/29 14:29:53 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	a;
	unsigned int	b;

	a = 0;
	if (s && f)
	{
		b = ft_strlen(s);
		while (a < b)
		{
			f(a, s);
			a++;
			s++;
		}
	}
}
