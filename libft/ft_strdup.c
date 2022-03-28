/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:15:42 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 17:02:51 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	int		a;
	int		b;

	b = 0;
	a = -1;
	while (s[b])
		b++;
	new = malloc(sizeof(char) * (b + 1));
	if (!new)
		return (NULL);
	while (++a < b)
		new[a] = s[a];
	new[a] = '\0';
	return (new);
}
