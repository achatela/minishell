/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:54:59 by achatela          #+#    #+#             */
/*   Updated: 2022/05/31 14:29:44 by achatela         ###   ########.fr       */
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

char	*get_end(char **env, int i, int j, int k)
{
	char	*tmp;
	char	*tmp2;

	tmp = get_env_var(env, "HOME", 0);
	if (!tmp)
		return (NULL);
	tmp2 = getcwd(NULL, 0);
	while (tmp[i] == tmp2[i])
		i++;
	j = i - 1;
	free(tmp);
	while (tmp2[++i])
		k++;
	tmp = malloc(sizeof(char) * k + 2);
	k = 0;
	if (j > 0 && tmp2[j - 1] && tmp2[j] && tmp2[j] != '/')
		j++;
	while (j > 0 && tmp2[j - 1] && tmp2[j] && tmp2[++j])
	{
		tmp[k] = tmp2[j];
		k++;
	}
	tmp[k] = '\0';
	free(tmp2);
	return (tmp);
}

void	get_fd(t_args *head, t_args *args, int fd, char **cmds)
{
	int	old_fd;

	old_fd = dup(0);
	close(0);
	fd = open(args->parsed_arg, O_RDONLY);
	if (fd < 0)
	{
		close(0);
		dup(old_fd);
		close(old_fd);
		printf("fd < 0\n");
		return ;
	}
	send_builtin(head, cmds);
	close(0);
	dup(old_fd);
	close(old_fd);
}
