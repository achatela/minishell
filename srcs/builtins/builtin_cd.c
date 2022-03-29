#include "minishell.h"

void	builtin_cd(char **cmds, int i)
{
	chdir(cmds[1]);
	return ;
}
