/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:02:56 by achatela          #+#    #+#             */
/*   Updated: 2021/12/02 17:43:20 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*alloc;
	size_t	a;

	a = 0;
	if (size == 0 || nmemb == 0)
	{
		alloc = malloc(sizeof(char) * 1);
		if (!alloc)
			return (NULL);
		return ((void *)alloc);
	}
	alloc = malloc(size * nmemb);
	if (!alloc)
		return (NULL);
	while (a < (size * nmemb))
	{
		alloc[a] = '\0';
		a++;
	}
	return ((void *)alloc);
}
