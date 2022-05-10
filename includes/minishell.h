/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:13:07 by cjimenez          #+#    #+#             */
/*   Updated: 2022/05/10 13:56:37 by achatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <dirent.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

extern char				**g_env;
typedef struct s_echo	t_echo;
struct s_echo
{
	int	print;
};

typedef struct s_args	t_args;
struct	s_args
{
	int		index;
	char	*parsed_arg;
	int		is_command;
	int		to_use;
	int		is_separator;
	t_echo	*echo;
	t_args	*next;
	t_args	*before;
};

char	**realloc_cmds(char **cmds, int i, char *cat);
char	**new_cmds(char **cmds, char *tmp);
char	*get_end(char **env, int i, int j, int k);
char	**remove_heredoc(t_args *args, char *tmp, char **cmds);
void	redir(t_args *args, char **cmds, t_args *head, int fd);
void	d_redir(t_args *args, char **cmds);
void	redir_in(t_args *args, char **cmds);
int		pip(t_args *args, int start, int fd, int last, char **cmds);
void	handler(int sig, siginfo_t *info, void *null);
int		is_separator(char *str, int i);
int		invalid_identifiers(char c);
char	*str_no_quotes(char *str, int i, int j, int k);
char	*parse_arg(char *str, int i);
char	**remove_var(char **env, char *tmp, int i, int j);
void	free_list(t_args *args);
void	fill_args(t_args *args, char *str, int index, char *pip);
char	**sep_no_quotes(char **cmds, int i, int j);
char	**new_parsing(char *cmd, int i, int j, int k);
int		builtin_echo(t_args *args);
void	parsing(char *cmd, t_echo *echo);
char	**str_to_tabs(char *cmd, int i, int j);
int		arg_number(char *cmd, int i, int j);
int		send_builtin(t_args *args, int j, char **cmds);
int		builtin_cd(t_args *args, int i);
void		builtin_exit(t_args *args);
char	*get_env_var(char **env, char *var, int i);
void	builtin_env(int i);
char	*get_prompt(int i);
void	builtin_export(char **env, t_args *args);
void	free_env(char **env, int i);
void	switch_pwds(char **env, int i, int j);
int		env_lines(char **env);
void	free_cmds(char **cmds, int i);
void	export_no_arg(char **env, int i, int j);
char	*cut_var_begin(char *str, int i, int j);
char	*cut_var_end(char *str, int i, int j);
void	builtin_unset(char **env, t_args *args);
char	*get_env_var(char **env, char *var, int i);
int		existing_var(char **env, t_args *args);
t_args	*init_args(t_args *args, char **cmds, t_echo *echo);
int		exec_bin(char **cmds, t_args *args);
char	*str_quotes(char *str);
char	**parse_separators(char **cmds, int i);
int		ft_check_access(char *file, int i);

#endif
