#include "minishell.h"


static int	has_sep(t_args *args)
{
	t_args	*head;

	head = args;
	while (head && head->next)
	{
		if (head->is_separator == 1)
			return (1);
		head = head->next;
	}
	if (head->is_separator == 1)
		return (1);
	return (0);
}

static void	here_doc(t_args *args, int i)
{
	char	*delimiter;
	char	*tmp;
	int		line;

	line = 0;
	if (args->next != NULL)
		delimiter = args->next->parsed_arg;
	else
		return ;
	while (i != 1)
	{
		line++;
		tmp = readline("> ");
		if (tmp == NULL)
		{
			printf("warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", line, delimiter); 
			break;
		}
		else if (ft_strcmp(tmp, delimiter) == 0)
			i = 1;
		free(tmp);
	}
}

static void	new_list(t_args *args, char *tmp)
{
	t_args	*head;
	t_args	*head_free;

	head = args;
	while (args && has_sep(args) == 1)
	{
		while (args /*&& args->next*/ && ft_strcmp(args->parsed_arg, tmp) != 0)
		{
			head = args;
			args = args->next;
		}
		if (args && /*args->next &&*/ ft_strcmp(args->parsed_arg, tmp) == 0)
		{
			args = head;
			head_free = args->next->next;
			head = args->next;
			args->next = args->next->next->next;
		//	head_free = args;
		//	head->next = args->next->next;
			free(head->parsed_arg);
			free(head);
			free(head_free->parsed_arg);
			free(head_free);
			(void)head;
		//	head_free = args;
		//	args = head->next;
		//	free(head);
		}
		else if (args->next != NULL)
			args = args->next;
	}
}

static char	**realloc_cmds(char **cmds, int i, char *cat)
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
		if (j == i ||  j == i + 1 || (j == i - 1 && i != 0 && ft_strcmp(cmds[i - 1], cat) == 0))
				j++;
		else
			new[k++] = ft_strdup(cmds[j++]);
	}
	new[k] = 0;
	free_cmds(cmds, 0);
	return(new);
}

static char	**new_cmds(char **cmds, char *tmp)
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

char	**remove_heredoc(t_args *args, char *tmp, char **cmds)
{
	t_args	*head;

	head = args;
	while (args)
	{
		while (args && ft_strcmp(tmp, args->parsed_arg) != 0)
			args = args->next;
		if (args && ft_strcmp(tmp, args->parsed_arg) == 0)
		{
			here_doc(args, 0);
			args = args->next;
		}
	}
	if (head->next != NULL && head->next->next != NULL)
	{
		new_list(head, tmp);
		cmds = new_cmds(cmds, tmp);
	}
	else
	{
		head->to_use = 0;
	}
	free(tmp);
	return (cmds);
}
