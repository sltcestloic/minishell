VPATH	=	srcs:srcs/execution:srcs/parsing:srcs/util

SRC		= 	minishell.c \
			function.c \
			set_env.c \
			copy_sort_lst.c \
			set_pwd.c \
			find_exec.c \
			redirect.c \
			pipe.c \
			cmd.c \
			cmd_util.c \
			env_var.c \
			parser.c \
			redirect_parsing.c \
			redirect_utils.c \
			substitute_env.c \
			substitute.c \
			substitute_redirect.c \
			substitute_split.c \
			substitute_utils.c \
			ft_splitlen.c \
			init.c

SRCS 		= $(addprefix srcs/, ${SRC})
OBJS		= $(addprefix objs/, ${SRC:.c=.o})
INCS		= includes
NAME		= minishell
HEADER		= ${INCS}/minishell.h ${INCS}/parsing.h ${INCS}/exec.h
MAKEFILE 	= Makefile
LIBC		= ar rcs
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -g3

objs/%.o: %.c ${INCS}/minishell.h ${INCS}/parsing.h ${INCS}/exec.h dirs
	${CC} ${CFLAGS} -c $< -o $@ -I ${INCS}

${NAME}: ${OBJS} ${HEADER} ${MAKEFILE}
	@${MAKE} bonus -C ./libft
	${CC} -o ${NAME} ${OBJS} libft/libft.a -lreadline -L /Users/$$USER/.brew/opt/readline/lib -I/Users/$$USER/.brew/opt/readline/include

dirs: objs
	@mkdir -p objs

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
