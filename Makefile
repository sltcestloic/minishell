# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 16:40:32 by lbertran          #+#    #+#              #
#    Updated: 2021/04/17 12:39:32 by lubourre         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRC		= 	minishell.c \
			execution/function.c \
			execution/set_env.c \
			execution/copy_sort_lst.c \
			execution/set_pwd.c \
			parsing/commands/echo_parsing.c \
			parsing/ft_splitcmds.c \
			parsing/parser.c \
			util/ft_splitlen.c \
			util/prompt.c 
			
SRCS 	= $(addprefix srcs/, ${SRC})
OBJS	= ${SRCS:.c=.o}
INCS	= includes
NAME	= minishell
LIBC	= ar rcs
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g3

srcs/%.o: srcs/%.c ${INCS}
	${CC} ${CFLAGS} -c $< -o $@ -I${INCS}

${NAME}: ${OBJS}
	@${MAKE} bonus -C ./libft
	${CC} -o ${NAME} ${OBJS} libft/libft.a -g3
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
