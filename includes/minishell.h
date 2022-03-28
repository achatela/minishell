#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include "../libft/libft.h"

int		builtin_echo(char **argv, int i);
char	**get_path(char **env, int i);

#endif
