SRC		= 	minishell.c \
			execution/function.c \
			execution/set_env.c \
			execution/copy_sort_lst.c \
			execution/set_pwd.c \
			execution/find_exec.c \
			execution/redirect.c \
			execution/pipe.c \
			parsing/commands/echo_parsing.c \
			parsing/env_var.c \
			parsing/ft_splitcmds.c \
			parsing/parser.c \
			parsing/treatment.c \
			util/cmd.c \
			util/ft_splitlen.c \
			util/init.c \
			util/prompt.c 
			
SRCS 	= $(addprefix srcs/, ${SRC})
OBJS	= ${SRCS:.c=.o}
INCS	= includes
NAME	= minishell
LIBC	= ar rcs
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

srcs/%.o: srcs/%.c ${INCS}
	${CC} ${CFLAGS} -c $< -o $@ -I${INCS} -g

${NAME}: ${OBJS}
	@${MAKE} bonus -C ./libft
	${CC} -o ${NAME} ${OBJS} libft/libft.a
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
