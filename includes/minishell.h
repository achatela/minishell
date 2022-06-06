/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjimenez <cjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:13:07 by cjimenez          #+#    #+#             */
/*   Updated: 2022/06/06 16:55:10 by achatela         ###   ########.fr       */
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
struct s_echo
{
	int	print;
};

typedef struct s_index	t_index;
struct	s_index
{
	int	i;
	int	j;
	int	k;
	int	l;
};

typedef struct s_args	t_args;
struct	s_args
{
	int		index;
	char	*parsed_arg;
	int		is_command;
	int		to_use;
	int		is_separator;
	t_args	*next;
};

typedef struct s_pipe	t_pipe;
struct	s_pipe
{
	int		fd;
	char	**cmds;
	t_args	*args;
};

/* Init_env */
char	*set_cmd(char *cmd, char *exit);
char	*get_shlvl(char *str, int i, char *to_free);
char	**init_env(char **env, int i, int k);
/* Init_env */

/* Built-in cd*/
char	*full_path(t_args *args);
void	builtin_cd(t_args *args, char *tmp);
int		simple_path_return(t_args *args, char *tmp);
int		simple_path(char *arg);
char	*parsed_path(char *str, int i, int j);
char	*home_path(t_args *args);
int		print_cd_errors(char *tmp, char *home, t_args *args);
int		cd_errors(t_args *args, char *tmp, char *home, char *tmp2);
void	cd_end(t_args *args, char *tmp);
/* Built-in cd*/

/* Sep_no_quotes */
char	**sep_no_quotes(char **cmds, int i, int j);
void	cmds_length(char **cmds, int *i, int *j, int *k);
void	cmds_length2(char **cmds, int *i, int *j, int *k);
void	cmds_length3(char **cmds, int *i, int *j, int *k);
char	*new_string(char **cmds, int i, int j, int k);
char	*new_is_string(char **cmds, int *j, int i);
char	*new_separator(char **cmds, int i, int j, int k);
char	*new_is_sep(char **cmds, int *j, int i);
/* Sep_no_quotes */

/* Parsing */
t_args	*skip_cmd(t_args *args);
t_args	*while_send_sep(t_args *args, int *i, t_args *head, char **cmds);
void	while_sep(t_args *args, char **cmds);
int		send_sep(t_args *args, char **cmds, char *sep);
char	**parsing_to_tabs(char *cmd, t_index *idx);
char	**init_cmds(char *cmds, t_args **args);
int		sep_error(t_args *args, char **cmds, t_args *head);
int		is_whitespace(char c);
int		isprintable(char c);
int		arg_num_quotes(char *cmd, int *i, int *j, int *k);
int		error_cmds_args(t_args *args, char **cmds, int i);
t_pipe	*init_pipe(int *i, char **cmds, t_args *args);
/* Parsing */

/* Exec */
void	get_ret_value(t_args *agrs, int ret);
int		child(char *path, char **cmds, t_args *args);
char	*get_cmd_char(int *i, char *cmd);
char	*check_dir(char *bin, char *cmd);
char	*path_join(const char *s1, const char *s2);
void	check_path(char **cmd, t_index *idx, char *path);
char	**args_exec_not_end(char **cmds, t_index *idxs);
int		isseparator(char *str, int i);
void	exec_bin_end(char **bin, char *path, int i, t_pipe exec);
char	**command_not_found(t_args *args, int i, char *str);
int		check_unset_path(int i, char *cmd);
/* Exec */

/* Pip */
int		pip(t_pipe *pipes, int start, int fd, int last);
//int		has_pip(t_args *args);
/* Pip */

//char	**realloc_cmds(char **cmds, int i, char *cat);
t_index	*init_idx(int i, int j, int k, int l);
int		var_d_length(char *str, int i, int j, int k);
char	**new_cmds(char **cmds, char *tmp);
char	*get_tmp(char *str, int i, int j);
void	length_d_dollar(char *str, int *i, int *length);
//t_args	*new_list(t_args *args, char *tmp);
int		spaces(char *cmd);
char	*cut_var_modif(char *str, int j);
char	*fill_ret(char *str, int i, int j, char *tmp);
int		is_shlvl(char *str);
void	var_str(char *str, t_index *idx, char *tmp);
int		has_sep(t_args *args);
void	get_fd(t_args *head, t_args *args, int fd, char **cmds);
t_args	*get_args(t_args *args);
int		is_last(t_args *args);
void	heredoc_handler(int sig, siginfo_t *info, void *null);
char	*get_end(char **env, int i, int j, int k);
char	**remove_heredoc(t_args **args, char *tmp, char **cmds);
void	redir(t_args *args, char **cmds, t_args *head, int fd);
void	d_redir(t_args *args, char **cmds);
int		redir_in(t_args *args, t_args *head, char **cmds);
void	handler(int sig, siginfo_t *info, void *null);
int		is_separator(char *str, int i);
int		invalid_identifiers(char c);
char	*str_no_quotes(char *str, int i, int j, int k);
char	*parse_arg(char *str, int i);
char	**remove_var(char **env, char *tmp, int i, int j);
void	free_list(t_args *args);
void	fill_args(t_args *args, char *str, int index, char *pip);
int		builtin_echo(t_args *args, int i);
void	parsing(char *cmd);
char	**str_to_tabs(char *cmd, int i, int j);
int		arg_number(char *cmd, int i, int j);
int		send_builtin(t_args *head, char **cmds);
void	builtin_exit(t_args *args);
char	*get_env_var(char **env, char *var, int i);
void	builtin_env(int i, t_args *args);
char	*get_prompt(int i);
void	builtin_export(char **env, t_args *args);
void	free_env(char **env, int i);
void	switch_pwds(char **env, int i, int j);
int		env_lines(char **env);
void	free_cmds(char **cmds, int i);
void	export_no_arg(char **env, int i, int j);
char	*cut_var_begin(char *str, int i, int j);
char	*cut_var_end(char *str, int i, int j);
void	builtin_unset(t_args *args);
char	*get_env_var(char **env, char *var, int i);
int		existing_var(char **env, t_args *args);
t_args	*init_args(t_args *args, char **cmds);
int		exec_bin(char **cmds, t_args *args, int i);
char	*str_quotes(char *str);
char	**parse_separators(char **cmds, int i);
int		ft_check_access(char *file, int i);
t_args	*ft_export(int value, char *export);
int		error_double_redir(char **cmds, t_args *args, t_args *head);

#endif
