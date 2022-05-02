/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:32:31 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/02 16:32:32 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_arg(char *str, int i)
{
	char	*ret;

	while (i != -1 && str[i])
	{
		if (str[i] == '"' || str[i] == 39)
			i = -2;
		i++;
	}
	if (i != -1)
		ret = str_no_quotes(str, 0, 0, 0);
	else
		ret = str_quotes(str);
	return (ret);
}
