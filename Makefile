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
			parsing/substitute_split.c \
			parsing/substitute_utils.c \
			util/cmd.c \
			util/ft_splitlen.c \
			util/init.c

SRCS 		= $(addprefix srcs/, ${SRC})
OBJS		= $(addprefix objs/, ${SRC:.c=.o})
#OBJS		= ${SRCS:.c=.o}
INCS		= includes
NAME		= minishell
HEADER		= ${INCS}/minishell.h ${INCS}/parsing.h ${INCS}/exec.h
MAKEFILE 	= Makefile
LIBC		= ar rcs
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
objs/%.o: srcs/%.c ${INCS}/minishell.h ${INCS}/parsing.h ${INCS}/exec.h dirs
	${CC} ${CFLAGS} -c $< -o $@ -I${INCS}
${NAME}: ${OBJS} ${HEADER} ${MAKEFILE}
	@${MAKE} bonus -C ./libft
	${CC} -o ${NAME} ${OBJS} libft/libft.a -lreadline -L /Users/$$USER/.brew/opt/readline/lib -I/Users/$$USER/.brew/opt/readline/include -fsanitize=address

dirs: objs
	@mkdir -p objs
	@mkdir -p objs/execution
	@mkdir -p objs/parsing
	@mkdir -p objs/util
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
.PHONY: all clean fclean re .c.o dirs
