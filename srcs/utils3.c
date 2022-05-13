/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:54:59 by achatela          #+#    #+#             */
/*   Updated: 2022/05/13 13:50:13 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*get_args(t_args *args)
{
	while (args && is_last(args) != 0 && args->next->is_separator != 2)
	{
		while (args && args->is_separator == 0)
			args = args->next;
		while (args && args->is_separator == 1)
			args = args->next;
	}
	return (args);
}

int	is_separator(char *str, int i)
{
	if ((str[i] == '>' && str[i + 1] == '>'))
		return (2);
	else if ((str[i] == '<' && str[i + 1] == '<'))
		return (2);
	else if ((str[i] == '|' && i != 0 && str[i - 1])
		|| (str[i] == '|' && str[i + 1]))
		return (1);
	else if ((str[i] == '<' && i != 0 && str[i - 1])
		|| (str[i] == '<' && str[i + 1]))
		return (1);
	else if ((str[i] == '>' && i != 0 && str[i - 1])
		|| (str[i] == '>' && str[i + 1]))
		return (1);
	return (0);
}

int	is_last(t_args *args)
{
	while (args)
	{
		while (args && args->is_separator == 0)
			args = args->next;
		if (args && args->is_separator == 1)
		{
			if ((args->parsed_arg[0] == '>' && args->parsed_arg[1] == '>'
					&& args->parsed_arg[2] == '\0')
				|| (args->parsed_arg[0] == '>' && args->parsed_arg[1] == '\0'))
				return (1);
			else if (args->parsed_arg[0] == '<')
				return (0);
		}
		else if (args && args->is_separator == 2)
			return (2);
		else
			return (0);
	}
	return (0);
}
