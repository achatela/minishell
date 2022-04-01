#include "minishell.h"

/*static char	*list_parsing(t_args *args, char *str)
{
	(void)args;
	return (str);
	//maxi parsing à faire + set args->to_print
}*/

static void	fill_args(t_args *args, char *str, int index)
{
	args->index = index;
	args->parsed_arg = str;
}

t_args	*init_args(t_args *args, char **cmds)
{
	int	i;

	i = 1;
	args = ft_lstnew(NULL);
	fill_args(args, cmds[0], 0);
	while (cmds[i] != NULL)
	{
		ft_lstadd_back(args, ft_lstnew(NULL));
		fill_args(ft_lstlast(args), cmds[i], i);
		i++;
	}
	return (args);
}
