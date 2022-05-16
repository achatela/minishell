/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:44:11 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/16 14:00:38 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f' || c == ' ')
		return (1);
	return (0);
}

static int	isprintable(char c)
{
	if (c <= 126 && c > 32)
		return (1);
	return (0);
}

static void	arg_num_quotes(char *cmd, int *i, int *j, int *k)
{
	(*j) = (*i);
	(*i)++;
	while (cmd[(*i)] && cmd[(*i)] != cmd[(*j)])
		(*i)++;
	if (cmd[(*i)] == '\0')
		return ;
	if ((*j) >= 1 && ft_isprint(cmd[(*j) + 1]) == 0)
		(*k)++;
	(*i)++;
}

static int	arg_number2(char *cmd, int i, int j, int k)
{
	if (cmd[i] != ' ' && ft_isprint(cmd[i]) == 1)
		k++;
	while (cmd[i] && is_whitespace(cmd[i]) == 1)
		i++;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == 39)
			arg_num_quotes(cmd, &i, &j, &k);
		else if (is_whitespace(cmd[i]) == 1)
		{
			if (cmd[i + 1] != ' ' && ft_isprint(cmd[i + 1]) == 1)
				k++;
			i++;
		}
		else if (cmd[i + 1] != ' ' && ft_isprint(cmd[i + 1] == 1))
			i++;
		else
			i++;
	}
	return (k);
}

char	**parsing_to_tabs(char *cmd, int i, int j, int k)
{
	char	**cmds;
	int		l;
	char	tmp;

	l = 0;
	if (cmd[0] == '\0')
		return (NULL);
	tmp = '\0';
	if (arg_number2(cmd, 0, 0, 0) == -1)
	{
		cmds = NULL;
		return (printf("Quotes non fermées\n"), cmds);
	}
	cmds = malloc(sizeof(char *) * (arg_number2(cmd, 0, 0, 0) + 2));
	if (!cmds)
		return (NULL);
	while (i < ft_strlen(cmd) && cmd[i])
	{
		if (l == arg_number2(cmd, 0, 0, 0) + 1)
			break ;
		while (cmd[i] && isprintable(cmd[i]) != 1)
			i++;
		k = i;
		while (cmd[i] && isprintable(cmd[i]) == 1)
		{
			if (cmd[i] == '"' || cmd[i] == 39)
			{
				j = i;
				i++;
				while (cmd[i] && cmd[i] != cmd[j])
				{
					i++;
					while (cmd[i] && cmd[i] == 32)
						i++;
				}
				i++;
			}
			else
				i++;
		}
		cmds[l] = malloc(sizeof(char) * ((i - (k)) + 3));
		if (!cmds[l])
			return (NULL);
		j = k;
		k = 0;
		while (j < i)
		{
			while ((cmd[j] == '"' || cmd[j] == 39))
			{
				tmp = cmd[j];
				j++;
				while (j < i && cmd[j] != tmp)
				{
					cmds[l][k] = cmd[j - 1];
					k++;
					j++;
				}
				cmds[l][k] = cmd[j - 1];
				cmds[l][k + 1] = cmd[j];
				k += 2;
				if (cmd[j] == tmp)
					j++;
			}
			if (cmd[j] != '"' && cmd[j] != 39)
			{
				if (cmd[j] == ' ' && cmd[j + 1])
					j++;
				else
				{
					cmds[l][k] = cmd[j];
					k++;
					j++;
				}
			}
			else
				j++;
		}
		cmds[l][k] = '\0';
		l++;
		i++;
	}
	cmds[l] = 0;
	return (cmds);
}
