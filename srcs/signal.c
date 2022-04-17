#include "minishell.h"

void	handler(int sig)
{
	char	*prompt;

	if (sig == SIGINT)
	{
		printf("\n");
		prompt = get_prompt(g_env, -1);
		printf("%s", prompt);
		free(prompt);
	}
	if (sig == SIGQUIT)
		printf("\b\b  \b\b");
}
