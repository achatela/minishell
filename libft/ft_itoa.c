/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:08:05 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 15:34:20 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_length(int n)
{
	int	a;

	a = 0;
	if (n < 0)
	{
		n = -n;
		a = 1;
	}
	while (n >= 10)
	{
		a++;
		n /= 10;
	}
	return (a + 2);
}

static char	*ft_min(char *nbr)
{
	char	*str;
	int		a;

	a = 0;
	str = malloc(sizeof(char) * 12);
	str[0] = '-';
	if (!str)
		return (NULL);
	while (a < 10)
	{
		str[a + 1] = nbr[a];
		a++;
	}
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		a;
	char	*nb;

	if (n == -2147483648)
		return (ft_min("2147483647"));
	a = ft_length(n);
	nb = malloc(sizeof(char) * a);
	if (!nb)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		nb[0] = '-';
	}
	nb[a - 1] = '\0';
	a -= 2;
	while (n >= 10 && a > 0)
	{
		nb[a] = (n % 10) + 48;
		n /= 10;
		a--;
	}
	nb[a] = (n % 10) + 48;
	return (nb);
}
