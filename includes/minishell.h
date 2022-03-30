#ifndef MINISHELL_H
# define MINISHELL_H

// Pour compiler : gcc *.c -I./includes ./libft/libft.a -lreadline

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "../libft/libft.h"

extern char	**g_env;

char	*ft_strjoin(char const *s1, char const *s2);
int		builtin_echo(char **argv, int i);
char	**get_path(char **env, int i);
void	parsing(char *cmd);
char	**str_to_tabs(char *cmd, int i, int j);
int		arg_number(char *cmd, int i, int j);
int		send_builtin(char **cmds);
int		builtin_cd(char **cmds, int i);
int		builtin_exit(char **cmds);
char	*get_env_var(char **env, char *var, int i);
void	builtin_env(char **env, int i);
char	*get_prompt(char **env, int i);
void	builtin_export(char **env, int i);
//char	*cd_paths(char *arg);

#endif
