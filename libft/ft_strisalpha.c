/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisalpha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:04:47 by cjimenez          #+#    #+#             */
/*   Updated: 2022/03/30 11:06:22 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strialpha(const char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
    while (str[i])
    {
        if ((str[i] < 'a' || str[i] > 'z')
            && (str[i] < 'A' || str[i] > 'Z'))
            return (0);
        i++;
    }
    return (1);
}