NAME		= minishell

VPATH		=	srcs:srcs/execution:srcs/parsing:srcs/util

OBJS_DIR	=	objs
INCS_DIR	=	includes

#===============================#
#            SOURCES            #
#===============================#

#             MAIN              #

SRC			= 	minishell.c

#           EXECUTION           #

SRC			+=	copy_sort_lst.c \
				find_exec.c \
				function.c \
				pipe.c \
				redirect.c \
				set_env.c \
				set_pwd.c

#            PARSING            #

SRC			+=	cmd_util.c \
				cmd.c \
				env_var.c \
				parser.c \
				redirect_parsing.c \
				redirect_utils.c \
				substitute_env.c \
				substitute_redirect.c \
				substitute_split.c \
				substitute_utils.c \
				substitute.c

#              UTIL             #

SRC			+=	ft_splitlen.c \
				init.c



SRCS 		= $(addprefix srcs/, ${SRC})
OBJS		= $(addprefix objs/, ${SRC:.c=.o})


HEADERS		= ${INCS_DIR}/minishell.h ${INCS_DIR}/parsing.h ${INCS_DIR}/exec.h
MAKEFILE 	= Makefile


LIBC		= ar rcs
RM			= rm -f


CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3

objs/%.o: %.c ${HEADERS} ${OBJS_DIR}
	${CC} ${CFLAGS} -c $< -o $@ -I ${INCS_DIR}

${NAME}: ${OBJS} ${MAKEFILE} 
	@${MAKE} bonus -C ./libft
	${CC} -o ${NAME} ${OBJS} libft/libft.a -lreadline -L /Users/$$USER/.brew/opt/readline/lib -I/Users/$$USER/.brew/opt/readline/include

${OBJS_DIR}:
	@mkdir -p ${OBJS_DIR}

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
