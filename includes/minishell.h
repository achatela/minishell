#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
 
int		builtin_echo(char **argv, int i);
char	**get_path(char **env, int i);
void	parsing(char *cmd);
char	**str_to_tabs(char *cmd, int i, int j, int length);
int		arg_number(char *cmd, int i, int j);
void	send_builtin(char **cmds);

#endif
