#include "minishell.h"

int	send_builtin(char **cmds)
{
	if (ft_strcmp(*cmds, "echo") == 0)
		return(builtin_echo(cmds, 1));
	else if (ft_strcmp(*cmds, "cd") == 0)
		return(builtin_cd(cmds, 0));
	else if (ft_strcmp(*cmds, "pwd") == 0)
		printf("%s\n", getcwd(NULL, 0));
	 else if (ft_strcmp(*cmds, "export") == 0)
	 	return (builtin_export(g_env, cmds), 0);
	else if (ft_strcmp(*cmds, "unset") == 0)
		return (builtin_unset(g_env, cmds), 0);
	else if (ft_strcmp(*cmds, "env") == 0)
		return (builtin_env(g_env, 0), 0);
	else if (ft_strcmp(*cmds, "exit") == 0)
		return(builtin_exit(cmds));
	return (-1);
}
