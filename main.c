#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	builtin_echo(argv, 1);
	return (0);
}
