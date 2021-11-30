#===============================#
#          PROJECT NAME         #
#===============================#

NAME		=	minishell

#===============================#
#             VPATH             #
#===============================#

VPATH		=	srcs:srcs/execution:srcs/parsing:srcs/util:libft

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
				lst_utilities.c \
				env_utilities.c \
				heredoc.c \
				built_in.c \
				error_utils.c \
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


#             LIBFT             #

LIBFT_SRCS	=	char/ft_isalnum.c \
				char/ft_isalpha.c \
				char/ft_isascii.c \
				char/ft_isdigit.c \
				char/ft_isprint.c \
				char/ft_iswhitespace.c \
				char/ft_tolower.c \
				char/ft_toupper.c \
				gnl/ft_get_next_line.c \
				int/ft_atoi.c \
				int/ft_intlen.c \
				int/ft_itoa.c \
				int/ft_uintlen.c \
				int/ft_uitoa.c \
				int/ft_ull_base.c \
				memory/ft_bzero.c \
				memory/ft_calloc.c \
				memory/ft_memccpy.c \
				memory/ft_memchr.c \
				memory/ft_memcmp.c \
				memory/ft_memcpy.c \
				memory/ft_memmove.c \
				memory/ft_memset.c \
				memory/ft_malloc.c \
				print/ft_putchar_fd.c \
				print/ft_putendl_fd.c \
				print/ft_putnbr_fd.c \
				print/ft_putstr_fd.c \
				string/ft_split.c \
				string/ft_strcat.c \
				string/ft_strchr.c \
				string/ft_strcmp.c \
				string/ft_strcpy.c \
				string/ft_strdup.c \
				string/ft_strichr.c \
				string/ft_strjoin.c \
				string/ft_strlcat.c \
				string/ft_strlcpy.c \
				string/ft_strlen.c \
				string/ft_strmapi.c \
				string/ft_strncmp.c \
				string/ft_strndup.c \
				string/ft_strnstr.c \
				string/ft_strrchr.c \
				string/ft_strtrim.c \
				string/ft_substr.c \
				list/ft_lstadd_back.c \
				list/ft_lstadd_front.c \
				list/ft_lstclear.c \
				list/ft_lstdelone.c \
				list/ft_lstiter.c \
				list/ft_lstlast.c \
				list/ft_lstmap.c \
				list/ft_lstnew.c \
				list/ft_lstsize.c

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
CFLAGS		=	-Wall -Wextra -Werror

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

${NAME}: ${OBJS} ${LIBFT_SRCS}
	@${MAKE} -C ./libft
	@echo "[${NAME}] Creating executable..."
	@${CC} -o ${NAME} ${OBJS} -lreadline -L ${LIBFT_DIR} -lft -L ${RL_DIR} -I ${RL_DIR_I}
	@echo "[${NAME}] ${GREEN}Compilation successful!${WHITE}"


#            .PHONY             #

.PHONY: all clean fclean re .c.o
