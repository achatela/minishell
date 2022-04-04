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

char	*str_no_quotes(char *str, int i, int j, int k);
char	*parse_arg(char *str, int i);
char	**remove_var(char **env, char *tmp, int i, int j);
void	free_list(t_args *args);
void	fill_args(t_args *args, char *str, int index);
char	**new_parsing(char *cmd, int i, int j, int k);
int		builtin_echo(t_args *args);
char	**get_path(char **env, int i);
void	parsing(char *cmd);
char	**str_to_tabs(char *cmd, int i, int j);
int		arg_number(char *cmd, int i, int j);
int		send_builtin(t_args *args, int j);
int		builtin_cd(t_args *args, int i);
int		builtin_exit(t_args *args);
char	*get_env_var(char **env, char *var, int i);
void	builtin_env(int i);
char	*get_prompt(char **env, int i);
void	builtin_export(char **env, t_args *args);
void	free_env(char **env, int i);
void	switch_pwds(char **env, int i, int j);
int		env_lines(char **env);
void	free_cmds(char **cmds, int i);
void	export_no_arg(char **env, int i, int j);
char	*cut_var_begin(char *str, int i, int j);
char	*cut_var_end(char *str, int i, int j);
void    builtin_unset(char **env, t_args *args);
char	*get_env_var(char **env, char *var, int i);
int		exisiting_var(char **env, t_args *args);
t_args	*init_args(t_args *args, char **cmds);

#endif
