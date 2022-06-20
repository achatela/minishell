NAME = minishell

SRCS =	srcs/main.c						\
		srcs/utils3.c					\
		srcs/utils4.c					\
		srcs/utils5.c					\
		srcs/parsing.c 					\
		srcs/parssing.c					\
		srcs/send_builtin.c 			\
		srcs/cat_heredoc.c				\
		srcs/cat_here_doc.c				\
		srcs/sep_no_quotes_utils.c		\
		srcs/parsing_utils.c			\
		srcs/redir.c					\
		srcs/str_quotes_utils.c			\
		srcs/str_to_tabs.c 				\
		srcs/sep_no_quotes.c			\
		srcs/parsing_to_tabs_utils.c	\
		srcs/redir_in.c					\
		srcs/utils.c 					\
		srcs/init_env.c					\
		srcs/test_pipe.c				\
		srcs/utils2.c 					\
		srcs/cd_paths.c					\
		srcs/get_env_var.c				\
		srcs/get_prompt.c				\
		srcs/switch_pwds.c				\
		srcs/export_no_arg.c			\
		srcs/existing_var.c				\
		srcs/str_no_quotes.c			\
		srcs/init_args.c				\
		srcs/parsing_to_tabs.c			\
		srcs/parse_arg.c				\
		srcs/str_quotes.c				\
		srcs/parse_separators.c			\
		srcs/signal.c					\
		srcs/str_quotes_utils2.c		\
		srcs/here_doc.c					\
		srcs/here_doc_utils.c			\
		srcs/builtins/builtin_env.c		\
		srcs/builtins/builtin_cd.c 		\
		srcs/builtins/cd_utils.c		\
		srcs/builtins/cd_utils2.c		\
		srcs/builtins/builtin_echo.c 	\
		srcs/builtins/builtin_exit.c 	\
		srcs/builtins/builtin_export.c	\
		srcs/builtins/builtin_unset.c	\
		srcs/exec/exec.c 				\
		srcs/exec/exec_utils.c			\
		srcs/exec/exec_utils2.c			\
		srcs/exec/exec_utils3.c			\
		srcs/parsing_utils2.c			\
		srcs/doc_here.c					\
		srcs/redir_in2.c				\
		srcs/redir_utils.c				\
	
LIBFT = libft/libft.a
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3
INC = -I./includes
RM = rm -rf

.c.o:
	${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}

all:	${NAME}

${NAME}:	${OBJS}
	make -C libft
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -lreadline -o ${NAME}
	
clean:
	make clean -C libft
	${RM} ${OBJS}

fclean: clean
	${RM} ${LIBFT}
	${RM} ${NAME}

re: clean all

.PHONY: all clean fclean re
