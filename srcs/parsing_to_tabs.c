/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_to_tabs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:44:11 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/01 12:59:23 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_number2(char *cmd, int i, int j, int k)
{
	if (cmd[i] != ' ' && ft_isprint(cmd[i]) == 1)
		k++;
	while (cmd[i] && is_whitespace(cmd[i]) == 1)
		i++;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == 39)
		{
			if (arg_num_quotes(cmd, &i, &j, &k) == -1)
				return (-1);
		}
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

static void	while1(char *cmd, char **cmds, t_index *idx)
{
	char	tmp;

	tmp = '\0';
	while ((cmd[idx->j] == '"' || cmd[idx->j] == 39))
	{
		tmp = cmd[idx->j++];
		while (idx->j < idx->i && cmd[idx->j] != tmp)
			cmds[idx->l][idx->k++] = cmd[idx->j++ - 1];
		cmds[idx->l][idx->k] = cmd[idx->j - 1];
		cmds[idx->l][idx->k + 1] = cmd[idx->j];
		idx->k += 2;
		if (cmd[idx->j] == tmp)
			idx->j++;
	}
	if (cmd[idx->j] != '"' && cmd[idx->j] != 39)
	{
		if (cmd[idx->j] == ' ' && cmd[idx->j + 1])
			idx->j++;
		else
			cmds[idx->l][idx->k++] = cmd[idx->j++];
	}
	else
		idx->j++;
}

static void	parsing_to_tabs2(char *cmd, char **cmds, t_index *idx)
{
	while (cmd[idx->i] && isprintable(cmd[idx->i]) != 1)
		idx->i++;
	idx->k = idx->i;
	while (cmd[idx->i] && isprintable(cmd[idx->i]) == 1)
	{
		if (cmd[idx->i] && (cmd[idx->i] == '"' || cmd[idx->i] == 39))
		{
			idx->j = idx->i;
			idx->i++;
			while (cmd[idx->i] && cmd[idx->i] != cmd[idx->j])
				idx->i++;
			if (cmd[idx->i])
				idx->i++;
		}
		else
			idx->i++;
	}
	cmds[idx->l] = malloc(sizeof(char) * ((idx->i - (idx->k)) + 3));
	if (!cmds[idx->l])
		return ;
	idx->j = idx->k;
	idx->k = 0;
}

char	**parsing_to_tabs(char *cmd, t_index *idx)
{
	char	**cmds;

	if (cmd[0] == '\0')
		return (NULL);
	if (arg_number2(cmd, 0, 0, 0) == -1)
	{
		cmds = NULL;
		free(idx);
		return (printf("Quotes non fermées\n"), cmds);
	}
	cmds = malloc(sizeof(char *) * (arg_number2(cmd, 0, 0, 0) + 2));
	if (!cmds)
		return (NULL);
	while (idx->i < ft_strlen(cmd) && cmd[idx->i])
	{
		if (idx->l == arg_number2(cmd, 0, 0, 0) + 1)
			break ;
		parsing_to_tabs2(cmd, cmds, idx);
		while (idx->j < idx->i)
			while1(cmd, cmds, idx);
		cmds[idx->l++][idx->k] = '\0';
		idx->i++;
	}
	cmds[idx->l] = 0;
	return (free(idx), cmds);
}
