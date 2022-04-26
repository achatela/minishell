#include "minishell.h"

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

static void	remove_list(t_args *args)
{
	t_args	*head;

	head = args;
	if (args && args->next != NULL)
		args = args->next;
	(void)head;
	if (args->next->parsed_arg != NULL)
	{
		return ;
	}
}

void	remove_heredoc(t_args *args, char *tmp)
{
	t_args *head;

	head = args;
	while (args)
	{
		while (args && ft_strcmp(tmp, args->parsed_arg) != 0)
		{
			head = args;
			args = args->next;
		}
		if (args && ft_strcmp(tmp, args->parsed_arg) == 0)
		{
			here_doc(args, 0);
			(void)head;
			(void)remove_list;
			args = args->next;
		}
	}
	free(tmp);
}
