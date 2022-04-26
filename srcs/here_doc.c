#include "minishell.h"

void	here_doc(t_args *args, int i)
{
	char	*delimiter;
	char	*tmp;

	delimiter = args->next->parsed_arg;
	while (i != 1)
	{
		tmp = readline(">");
		if (ft_strcmp(tmp, delimiter) == 0)
			i = 1;
		free(tmp);
	}
}
