/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:39:21 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/22 17:24:18 by cjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	send_builtin(t_args *head, char **cmds)
{
	char		*tmp;

	if (head == NULL)
		return (1);
	tmp = getcwd(NULL, 0);
	if (tmp == NULL && ft_strcmp(head->parsed_arg, "pwd") == 0)
		tmp = get_env_var(g_env, "PWD", 0);
	if (ft_strcmp(head->parsed_arg, "echo") == 0)
		return (free(tmp), builtin_echo(head, 0));
	else if (ft_strcmp(head->parsed_arg, "cd") == 0)
		return (free(tmp), builtin_cd(head, NULL), 0);
	else if (ft_strcmp(head->parsed_arg, "pwd") == 0)
		printf("%s\n", tmp);
	else if (ft_strcmp(head->parsed_arg, "export") == 0)
		return (free(tmp), builtin_export(g_env, head), 0);
	else if (ft_strcmp(head->parsed_arg, "unset") == 0)
		return (free(tmp), builtin_unset(head), 0);
	else if (ft_strcmp(head->parsed_arg, "env") == 0)
		return (free(tmp), builtin_env(0, head), 0);
	else if (ft_strcmp(head->parsed_arg, "exit") == 0)
		return (free(tmp), builtin_exit(head), 0);
	else
		exec_bin(cmds, head, 0);
	free(tmp);
	return (-1);
}
