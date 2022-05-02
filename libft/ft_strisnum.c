/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmsjuice <cmsjuice@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:50:46 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/02 14:11:30 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	else if (str[1] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '"')
			i++;
		else if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
