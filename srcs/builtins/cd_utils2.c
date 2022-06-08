/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:37:27 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/08 17:41:05 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_path(t_args *args, char *tmp, char *tmp2, char *home)
{
	if (args->next == NULL
		|| (args->next != NULL && args->next->parsed_arg[0] == '~')
		|| (args->next != NULL && args->next->is_separator == 1))
	{
		if (args->next == NULL || tmp2 == NULL)
			chdir(home);
		else if (tmp2 != NULL)
		{
			if (chdir(tmp) == 0)
				chdir(tmp2);
			free(tmp2);
		}
		free(home);
		switch_pwds(g_env, 0, 0);
		return (1);
	}
	printf("%s: Not a directory\n", tmp);
	free(home);
	free(tmp2);
	return (0);
}
