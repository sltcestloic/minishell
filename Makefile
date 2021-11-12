#===============================#
#          PROJECT NAME         #
#===============================#

NAME		=	minishell

#===============================#
#             VPATH             #
#===============================#

VPATH		=	srcs:srcs/execution:srcs/parsing:srcs/util

#===============================#
#              DIRS             #
#===============================#

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



SRCS 		=	${SRC}
OBJS		=	$(addprefix objs/, ${SRC:.c=.o})


HEADERS		=	${INCS_DIR}/minishell.h ${INCS_DIR}/parsing.h ${INCS_DIR}/exec.h
MAKEFILE 	=	Makefile


LIBC		=	ar rcs
RM			=	rm -f


CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3

#===============================#
#            COLORS             #
#===============================#

BLACK		=	\x1b[30m
RED			=	\x1b[31m
GREEN		=	\x1b[32m
YELLOW		=	\x1b[33m
BLUE		=	\x1b[34m
PURPLE		=	\x1b[35m
CYAN		=	\x1b[36m
WHITE		=	\x1b[37m

${OBJS_DIR}/%.o: %.c ${HEADERS} ${MAKEFILE} 
	@mkdir -p ${OBJS_DIR}
	@${CC} ${CFLAGS} -c $< -o $@ -I ${INCS_DIR}
	@echo "[${NAME}] Compiling ${YELLOW}$<${WHITE}"

${NAME}: ${OBJS}
	@${MAKE} bonus -C ./libft
	@echo "[${NAME}] Creating executable..."
	@${CC} -o ${NAME} ${OBJS} libft/libft.a -lreadline -L /Users/$$USER/.brew/opt/readline/lib -I/Users/$$USER/.brew/opt/readline/include
	@echo "[${NAME}] ${GREEN}Compilation successful!${WHITE}"

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
