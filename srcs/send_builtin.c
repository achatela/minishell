/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:39:21 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/13 15:45:11 by achatela         ###   ########.fr       */
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
		return (free(tmp), builtin_cd(head, 0), 0);
	else if (ft_strcmp(head->parsed_arg, "pwd") == 0)
		printf("%s\n", tmp);
	else if (ft_strcmp(head->parsed_arg, "export") == 0)
		return (free(tmp), builtin_export(g_env, head), 0);
	else if (ft_strcmp(head->parsed_arg, "unset") == 0)
		return (free(tmp), builtin_unset(g_env, head), 0);
	else if (ft_strcmp(head->parsed_arg, "env") == 0)
		return (free(tmp), builtin_env(0), 0);
	else if (ft_strcmp(head->parsed_arg, "exit") == 0)
		return (free(tmp), builtin_exit(head), 0);
	else
		exec_bin(cmds, head);
	free(tmp);
	return (-1);
}
