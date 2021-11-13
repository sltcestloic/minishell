#===============================#
#          PROJECT NAME         #
#===============================#

NAME		=	minishell

#===============================#
#             VPATH             #
#===============================#

VPATH		=	srcs:srcs/execution:srcs/parsing:srcs/util

#===============================#
#             DIRS              #
#===============================#

OBJS_DIR	=	objs
INCS_DIR	=	includes
LIBFT_DIR	=	./libft/
RL_DIR		=	/Users/$$USER/.brew/opt/readline/lib
RL_DIR_I	=	/Users/$$USER/.brew/opt/readline/include

#===============================#
#            SOURCES            #
#===============================#

#             MAIN              #

SRCS		= 	minishell.c

#           EXECUTION           #

SRCS		+=	copy_sort_lst.c \
				find_exec.c \
				function.c \
				pipe.c \
				redirect.c \
				set_env.c \
				set_pwd.c \
				signal.c

#            PARSING            #

SRCS		+=	cmd_util.c \
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

SRCS		+=	ft_splitlen.c \
				init.c \
				util.c

#===============================#
#            OBJECTS            #
#===============================#

OBJS		=	$(addprefix objs/, ${SRCS:.c=.o})

#===============================#
#             FILES             #
#===============================#

HEADERS		=	${INCS_DIR}/minishell.h ${INCS_DIR}/parsing.h ${INCS_DIR}/exec.h
MAKEFILE 	=	Makefile

#===============================#
#            COMMANDS           #
#===============================#

RM			=	rm -f

#===============================#
#            COMPILER           #
#===============================#

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address

#===============================#
#             COLORS            #
#===============================#

BLACK		=	\x1b[30m
RED			=	\x1b[31m
GREEN		=	\x1b[32m
YELLOW		=	\x1b[33m
BLUE		=	\x1b[34m
PURPLE		=	\x1b[35m
CYAN		=	\x1b[36m
WHITE		=	\x1b[37m

#===============================#
#             RULES             #
#===============================#

#          MAIN RULES           #

all: ${NAME} 

bonus: all

re: fclean all

#        CLEANING RULES         #

clean:
	${MAKE} clean -C ./libft
	${RM} ${OBJS}
	${RM} a.out

fclean: clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}

#       COMPILATION RULES       #

${OBJS_DIR}/%.o: %.c ${HEADERS} ${MAKEFILE} 
	@mkdir -p ${OBJS_DIR}
	@${CC} ${CFLAGS} -c $< -o $@ -I ${INCS_DIR}
	@echo "[${NAME}] Compiling ${YELLOW}$<${WHITE}"

${NAME}: ${OBJS}
	@${MAKE} bonus -C ./libft
	@echo "[${NAME}] Creating executable..."
	@${CC} -o ${NAME} ${OBJS} -lreadline -L ${LIBFT_DIR} -lft -L ${RL_DIR} -I ${RL_DIR_I} -fsanitize=address
	@echo "[${NAME}] ${GREEN}Compilation successful!${WHITE}"


#            .PHONY             #

.PHONY: all clean fclean re .c.o dirs
