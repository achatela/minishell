#include "minishell.h"

void	handler(int sig)
{
//	char	*prompt;

	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		printf("\b\b  \b\b");
}
