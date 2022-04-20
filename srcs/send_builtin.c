#include "minishell.h"

static int	get_next_index(t_args *args, int i)
{
	int		j;
	t_args	*head;

	head = args;
	j = -1;
	while (head && ++j < i && head->is_command != 1)
		head = head->next;
	if (head == NULL)
		return (-1);
	else
		return (j);
}

/* Faire qqch comme while (args != NULL) > fork dans 
 * send_builtin quand on gèrera les separateurs */

int	send_builtin(t_args *args, int j, char **cmds)
{
//	static int	i = 0;
	t_args		*head;
	char		*tmp;

	head = args;
	tmp = getcwd(NULL, 0);
	(void)j;
	(void)get_next_index;
//	while (head && ++j < i)
//		head = head->next;
	if (ft_strcmp(head->parsed_arg, "echo") == 0)
		return(free(tmp), builtin_echo(head));								
	else if (ft_strcmp(head->parsed_arg, "cd") == 0)
		return(free(tmp), builtin_cd(head, 0));
	else if (ft_strcmp(head->parsed_arg, "pwd") == 0)
		printf("%s\n", tmp);
	 else if (ft_strcmp(head->parsed_arg, "export") == 0)
	 	return (free(tmp), builtin_export(g_env, head), 0);
	else if (ft_strcmp(head->parsed_arg, "unset") == 0)
		return (free(tmp), builtin_unset(g_env, head), 0);
	else if (ft_strcmp(head->parsed_arg, "env") == 0)
		return (free(tmp), builtin_env(0), 0);
	else if (ft_strcmp(head->parsed_arg, "exit") == 0)
		return(free(tmp), builtin_exit(head));
	else 
		exec_bin(cmds, head);
	free(tmp);
//	i = get_next_index(args, i);
	return (-1); //dans parsing, if return value = -1, envoyer dans exec custom (sans command_not_found)
}				// pour recup la valeur de retour dans echo->print
