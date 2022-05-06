/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:45:11 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/06 16:34:49 by cjimenez         ###   ########.fr       */
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
	if (access(file, F_OK) == -1)
	{
		printf("%s: No such file or directory\n", file);
		return (-1);
	}
	else if (access(file, W_OK) == -1)
	{
		printf("%s: Permission denied\n", file);
		return (-1);
	}
	else if (access(file, R_OK) == -1)
	{
		printf("%s: No such file or directory\n", file);
		return (-1);
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

char	**realloc_cmds(char **cmds, int i, char *cat)
{
	int		j;
	int		k;
	char	**new;

	k = 0;
	j = 0;
	while (cmds[j] != 0)
		j++;
	if (i != 0 && ft_strcmp(cmds[i - 1], cat) == 0)
		j--;
	new = malloc(sizeof(char *) * (j - 1));
	if (!new)
		return (NULL);
	j = 0;
	while (cmds[j])
	{
		if (j == i || j == i + 1 || (j == i - 1 && i != 0
				&& ft_strcmp(cmds[i - 1], cat) == 0))
				j++;
		else
			new[k++] = ft_strdup(cmds[j++]);
	}
	new[k] = 0;
	free_cmds (cmds, 0);
	return (new);
}

char	**new_cmds(char **cmds, char *tmp)
{
	int	i;

	i = 0;
	while (cmds[i] != 0)
	{
		if (ft_strcmp(cmds[i], tmp) == 0)
		{
			cmds = realloc_cmds(cmds, i, "cat");
			i = -1;
		}
		i++;
	}
	return (cmds);
}
