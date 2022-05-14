/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:48:37 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/14 18:16:14 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoll(const char *nptr)
{
	long long	number;
	long long	a;
	long long	neg;

	neg = 1;
	a = 0;
	number = 0;
	while (nptr[a] == '\t' || nptr[a] == '\n' || nptr[a] == '\r'
		|| nptr[a] == '\v' || nptr[a] == '\f' || nptr[a] == ' ')
		a++;
	if (nptr[a] == '-' || nptr[a] == '+')
	{
		if (nptr[a] == '-')
			neg = -1;
		a++;
	}
	while (nptr[a] >= '0' && nptr[a] <= '9')
	{
		number = number * 10 + (nptr[a] - '0');
		a++;
	}
	return (number * neg);
}
