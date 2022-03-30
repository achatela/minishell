NAME = minishell

SRCS =	srcs/main.c						\
		srcs/get_path.c 				\
		srcs/parsing.c 					\
		srcs/send_builtin.c 			\
		srcs/str_to_tabs.c 				\
		srcs/utils.c 					\
		srcs/cd_paths.c					\
		srcs/get_env_var.c				\
		srcs/builtins/builtin_env.c		\
		srcs/builtins/builtin_cd.c 		\
		srcs/builtins/builtin_echo.c 	\
		srcs/builtins/builtin_exit.c 	\

LIBFT = libft/libft.a
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror
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
