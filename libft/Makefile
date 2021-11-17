# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 16:40:32 by lbertran          #+#    #+#              #
#    Updated: 2021/11/17 08:45:09 by lbertran         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS		=	char/ft_isalnum.c \
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
				string/ft_split_nofree.c \
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
				string/ft_substr.c

SRCS_BONUS	=	list/ft_lstadd_back.c \
				list/ft_lstadd_front.c \
				list/ft_lstclear.c \
				list/ft_lstdelone.c \
				list/ft_lstiter.c \
				list/ft_lstlast.c \
				list/ft_lstmap.c \
				list/ft_lstnew.c \
				list/ft_lstsize.c

OBJS		= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

INCS		= .
HEADER		= libft.h
Makefile	= Makefile
NAME		= libft.a
LIBC		= ar rc
CC	= gcc
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror

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

%.o: %.c ${HEADER} ${MAKEFILE} 
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCS}
	@echo "[${NAME}] Compiling ${YELLOW}$<${WHITE}"

$(NAME): ${OBJS}
	@${LIBC} ${NAME} ${OBJS}

bonus: ${OBJS_BONUS} all
	@echo "[${NAME}] Creating library..."
	@${LIBC} ${NAME} ${OBJS} ${OBJS_BONUS}
	@echo "[${NAME}] ${GREEN}Compilation successful!${WHITE}"


all: ${NAME}

clean:
	${RM} ${OBJS}
	${RM} ${OBJS_BONUS}
	${RM} a.out

fclean: clean
	${RM} ${NAME}

re: fclean all
	
.PHONY: all clean fclean re bonus
