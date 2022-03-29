#include "minishell.h"

void	builtin_cd(char **cmds, int i)
{
	if (cmds[1] == NULL)
	{
		chdir("~");
		return ;
	}
	chdir(cmds[1]);
	return ;
}
