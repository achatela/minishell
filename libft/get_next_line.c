/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:56:41 by achatela          #+#    #+#             */
/*   Updated: 2021/12/17 13:14:08 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static int	ft_check_nl(char *buffer, int i)
{
	while (buffer[i] != '\0' && buffer[i] != '\n' && i < BUFFER_SIZE)
		i++;
	if (buffer[i] == '\n')
		return (0);
	else
		return (1);
}

static void	ft_fill_buffer(char *buffer, int j)
{
	int	i;

	i = 0;
	j += 1;
	while (j < BUFFER_SIZE && buffer[j] != '\0')
	{
		buffer[i] = buffer[j];
		i++;
		j++;
	}
	buffer[i] = '\0';
}	

static void	reset_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		buffer[i] = '\0';
		i++;
	}
}

static char	*ft_fill_ret(char *ret, char *buffer, int i, int fd)
{
	int	j;

	while (i != 0)
	{
		if (ft_check_nl(buffer, 0) == 0)
		{
			j = 0;
			ret = ft_strjoin_nl(ret, buffer, 0);
			while (buffer[j] != '\n')
				j++;
			if (j != BUFFER_SIZE - 1 && BUFFER_SIZE != 1)
				ft_fill_buffer(buffer, j);
			else
				reset_buffer(buffer);
			return (ret);
		}
		ret = ft_strjoin(ret, buffer);
		reset_buffer(buffer);
		i = read(fd, buffer, BUFFER_SIZE);
	}
	reset_buffer(buffer);
	if (i == 0)
		return (ret);
	free(ret);
	return (NULL);
}

char	*get_next_line(int fd)
{
	int			i;
	static char	buffer[BUFFER_SIZE + 1];
	char		*ret;
	int			j;

	j = 0;
	while (buffer[j] != '\0')
		j++;
	if (buffer[0] != '\0')
		i = 1;
	else
		i = read(fd, (&buffer + j), (BUFFER_SIZE - j));
	if (i <= 0)
		return (NULL);
	ret = malloc(sizeof(char) * 1);
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	ret = ft_fill_ret(ret, buffer, i, fd);
	return (ret);
}
