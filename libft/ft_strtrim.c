/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:07:30 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 13:45:47 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_start(char const *s1, char const *set)
{
	int	a;
	int	b;

	a = 0;
	while (s1[a] < 32)
		a++;
	while (s1[a])
	{
		b = 0;
		while (set[b] != s1[a] && set[b])
			b++;
		if (set[b] == '\0')
			return (a);
		a++;
	}
	return (0);
}

static int	ft_end(char const *s1, char const *set)
{
	int	a;
	int	b;

	a = ft_strlen(s1);
	while (a > 0 && s1[a] < 32)
		a--;
	while (a > 0)
	{
		b = 0;
		while (set[b] != s1[a] && set[b])
			b++;
		if (set[b] == '\0')
			return (a);
		a--;
	}
	return (a);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		b;
	int		c;
	int		d;

	if (s1[0] == '\0' || (ft_end(s1, set) == 0 && ft_start(s1, set) == 0))
	{
		str = malloc(sizeof(char) * 1);
		str[0] = '\0';
		return (str);
	}
	d = ft_start(s1, set);
	c = 0;
	b = (ft_end(s1, set) - ft_start(s1, set) + 2);
	str = malloc(sizeof(char) * b);
	if (!str)
		return (NULL);
	while (c < b - 1 && s1[d])
	{
		str[c] = s1[d];
		c++;
		d++;
	}
	str[c] = '\0';
	return (str);
}
