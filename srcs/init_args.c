#include "minishell.h"

/*static char	*list_parsing(t_args *args, char *str)
{
	(void)args;
	return (str);
	//maxi parsing à faire + set args->to_print
}*/

static int	str_is_sep(char *str)
{
	if (ft_strlen(str) > 3)
		return (0);
	else if (str[0] == '|' && str[1] == '\0')
		return (1);
	else if (str[0] == '<' && str[1] == '\0')
		return (1);
	else if (str[0] == '>' && str[1] == '\0')
		return (1);
	else if (str[0] == '<' && str[1] == '<'
			&& str[2] == '\0')
		return (1);
	else if (str[0] == '>' && str[1] == '>'
			&& str[2] == '\0')
		return (1);
	else
		return (0);

}

void	fill_args(t_args *args, char *str, int index)
{
	//redéfinir is_separator en fonction de str
	if (index == 0)
	{
		args->to_use = 0;
		args->is_command = 1;
	}
	else if (index > 0)
	{
		args->to_use = 1;
		args->is_command = 0;
	}
	args->is_separator = 0;
	if (str_is_sep(str) == 1)
		args->is_separator = 1;
	args->index = index;
//	args->parsed_arg = str;
	args->parsed_arg = parse_arg(str, 0);
}

t_args	*init_args(t_args *args, char **cmds)
{
	int	i;

	i = 1;
	while (cmds[i] != NULL)
	{
		ft_lstadd_back(args, ft_lstnew(NULL));
		fill_args(ft_lstlast(args), cmds[i], i);
		i++;
	}
	return (args);
}
