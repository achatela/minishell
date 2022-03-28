/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 16:11:47 by achatela          #+#    #+#             */
/*   Updated: 2021/12/17 13:14:10 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	return (i);
}

char	*ft_strjoin_nl(char *s1, char *s2, int i)
{
	char	*str;
	int		j;

	j = 0;
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 2));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\n' && j < BUFFER_SIZE)
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\n';
	str[i + 1] = '\0';
	free(s1);
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		a;
	int		b;

	b = 0;
	a = 0;
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!str)
		return (NULL);
	while (s1[a] != '\0')
	{
		str[a] = s1[a];
		a++;
	}
	while (s2[b] != '\0')
	{
		str[a] = s2[b];
		a++;
		b++;
	}
	str[a] = '\0';
	free(s1);
	return (str);
}
