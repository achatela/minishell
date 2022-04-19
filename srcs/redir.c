#include "minishell.h"

void	redir(t_args *args)
{
	int	fdd;
	int	pid;

	dup2(fdd, 1);
	pid = fork();
}
