/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:36:20 by cjimenez          #+#    #+#             */
/*   Updated: 2022/04/05 12:36:18 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_memdel(void *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = NULL;
    }
    return (NULL);
}