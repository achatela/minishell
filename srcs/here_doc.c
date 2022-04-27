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
	delimiter = args->next->parsed_arg;
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
		while (args && args->next && ft_strcmp(args->next->parsed_arg, tmp) != 0)
		{
			head = args;
			args = args->next;
		}
		if (args && ft_strcmp(args->next->parsed_arg, tmp) == 0)
		{
			args->next = args->next->next->next;
		//	head_free = args;
		//	head->next = args->next->next;
			(void)head;
			(void)head_free;
		//	head_free = args;
		//	args = head->next;
		//	free(head);
		}
		else if (args->next != NULL)
			args = args->next;
	}
}

void	remove_heredoc(t_args *args, char *tmp)
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
	new_list(head, tmp);
	free(tmp);
}
