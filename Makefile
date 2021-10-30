SRC		= 	minishell.c \
			execution/function.c \
			execution/set_env.c \
			execution/copy_sort_lst.c \
			execution/set_pwd.c \
			execution/find_exec.c \
			execution/redirect.c \
			execution/pipe.c \
			parsing/cmd.c \
			parsing/cmd_util.c \
			parsing/env_var.c \
			parsing/parser.c \
			parsing/redirect.c \
			parsing/redirect_utils.c \
			parsing/substitute_env.c \
			parsing/substitute.c \
			parsing/substitute_redirect.c \
			parsing/substitute_utils.c \
			util/cmd.c \
			util/ft_splitlen.c \
			util/init.c

SRCS 	= $(addprefix srcs/, ${SRC})
OBJS	= ${SRCS:.c=.o}
INCS	= includes
NAME	= minishell
LIBC	= ar rcs
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address
srcs/%.o: srcs/%.c ${INCS}
	${CC} ${CFLAGS} -c $< -o $@ -I${INCS} -g
${NAME}: ${OBJS}
	@${MAKE} bonus -C ./libft
	${CC} -o ${NAME} ${OBJS} libft/libft.a -lreadline -L /Users/$$USER/.brew/opt/readline/lib -I/Users/$$USER/.brew/opt/readline/include -fsanitize=address
all: ${NAME}
bonus: all
clean:
	${MAKE} clean -C ./libft
	${RM} ${OBJS}
	${RM} a.out
fclean: clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}
re: fclean all
.PHONY: all clean fclean re .c.o
