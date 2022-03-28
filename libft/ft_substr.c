/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:56:51 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 17:27:40 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_check(char const *s, unsigned int start)
{
	char	*str;

	if (start > (unsigned int)ft_strlen(s))
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	else
		return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	a;
	size_t	b;

	if (start > (unsigned int)ft_strlen(s))
		return (ft_check(s, start));
	b = start;
	while (s[b])
		b++;
	a = 0;
	if (len < (b - start + 1))
		str = malloc(sizeof(char) * len + 1);
	else
		str = malloc(sizeof(char) * (b - start + 1));
	if (!str)
		return (NULL);
	while (s[start] && a < len)
	{
		str[a] = s[start];
		start++;
		a++;
	}
	str[a] = '\0';
	return (str);
}
