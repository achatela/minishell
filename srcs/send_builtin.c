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

int	send_builtin(t_args *args, int j)
{
	static int	i = 0;
	t_args		*head;

	head = args;
	while (head && ++j < i)
		head = head->next;
	if (ft_strcmp(head->parsed_arg, "echo") == 0)
		return(builtin_echo(head));								/*Remplacer par strncmp partout parce que "command   " == invalid*/
	else if (ft_strcmp(head->parsed_arg, "cd") == 0)
		return(builtin_cd(head, 0));
	else if (ft_strcmp(head->parsed_arg, "pwd") == 0)
		printf("%s\n", getcwd(NULL, 0));/*
	 else if (ft_strcmp(head->parsed_arg, "export") == 0)
	 	return (builtin_export(g_env, head), 0);
	else if (ft_strcmp(head->parsed_arg, "unset") == 0)
		return (builtin_unset(g_env, head), 0);
	else if (ft_strcmp(head->parsed_arg, "env") == 0)
		return (builtin_env(g_env, 0), 0);
	else if (ft_strcmp(head->parsed_arg, "exit") == 0)
		return(builtin_exit(head));*/
	i = get_next_index(args, i);
	return (-1);
}
