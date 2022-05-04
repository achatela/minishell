/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:45:11 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/04 16:24:37 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_identifiers(char c)
{
	if ((c <= 13 && c >= 1) || c == '!' || c == '"' || c == '#'
		|| c == '$' || c == '%' || c == '&' || c == 39 || c == '('
		|| c == ')' || c == '*' || c == ';' || c == '<' || c == '>'
		|| c == '\\' || c == '`' || c == '{' || c == '}' || c == '|'
		|| c == 127 || c == '~')
		return (1);
	else
		return (0);
}

int	ft_check_access(char *file, int i)
{
	if (i == 1)
		printf("cd : ");
	if (access(file, R_OK) == -1)
	{
		printf("%s: No such file or directory\n", file);
		return (-1);
	}
	else if (access(file, W_OK) == -1)
	{
		printf("%s: Permission denied\n", file);
		return (-1);
	}
	else if (access(file, X_OK) == -1)
	{
		printf("%s: Permission denied\n", file);
		return (-1);
	}
	else if (access(file, F_OK) == -1)
	{
		printf("%s: No suck file or directory\n", file);
		return (-1);
	}
	return (0);
}