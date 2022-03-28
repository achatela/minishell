#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>

int		builtin_echo(char **argv, int i);
char	**get_path(char **env, int i);
char	**ft_split(char const *s, char c);
int		ft_strlen(char *str);

#endif
