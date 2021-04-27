/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:59:28 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/27 13:36:03 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
#  define FALSE 0
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_free
{
	void			*data;
	void			*next;
}				t_free;

/*
** Char
*/

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_iswhitespace(char c);
int				ft_toupper(int c);
int				ft_tolower(int c);

/*
** GNL
*/

int				ft_get_next_line(int fd, char **line);

/*
** Int
*/

int				ft_atoi(const char *str);
char			*ft_itoa(int n);
size_t			ft_intlen(long nbr);
size_t			ft_uintlen(unsigned long long nbr, int baselen);
char			*ft_uitoa(unsigned long long nbr);
char			*ft_ull_base(unsigned long long nbr, char *base);

/*
** List
*/

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *list);
t_list			*ft_lstlast(t_list *list);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
				void (*del)(void *));

/*
** Memory
*/

void			*ft_memset(void *s, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			ft_free(t_free *to_free);
void			ft_free_one(t_free **to_free);
char			*ft_malloc(int size, t_free **to_free);

/*
** Print
*/

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
** String
*/

size_t			ft_strcpy(char *dest, const char *src);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *c);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strtrim(const char *s1, const char *s2);
char			**ft_split(const char *s, char c);
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char			*ft_strndup(const char *s, size_t n);
int				ft_strichr(const char *s, int c);
void			free_split(char **ret);
char			*ft_strrdup(const char *str, int start, int end);

/*
** Text colors
*/

# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define MAGENTA "\e[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"

/*
** Regular bold text
*/
# define BBLACK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGREEN "\e[1;32m"
# define BYELLOW "\e[1;33m"
# define BBLUE "\e[1;34m"
# define BMAGENTA "\e[1;35m"
# define BCYAN "\e[1;36m"
# define BWHITE "\e[1;37m"

/*
** Regular underline text
*/
# define UBLACK "\e[4;30m"
# define URED "\e[4;31m"
# define UGREEN "\e[4;32m"
# define UYELLOW "\e[4;33m"
# define UBLUE "\e[4;34m"
# define UMAGENTA "\e[4;35m"
# define UCYAN "\e[4;36m"
# define UWHITE "\e[4;37m"

/*
** Regular background
*/
# define BLACKB "\e[40m"
# define REDB "\e[41m"
# define GREENB "\e[42m"
# define YELLOWB "\e[43m"
# define BLUEB "\e[44m"
# define MAGENTAB "\e[45m"
# define CYANB "\e[46m"
# define WHITEB "\e[47m"

/*
** High intensity background
*/
# define BLACKHB "\e[0;100m"
# define REDHB "\e[0;101m"
# define GREENHB "\e[0;102m"
# define YELLOWHB "\e[0;103m"
# define BLUEHB "\e[0;104m"
# define MAGENTAHB "\e[0;105m"
# define CYANHB "\e[0;106m"
# define WHITEHB "\e[0;107m"

/*
** High intensity text
*/
# define HBLACK "\e[0;90m"
# define HRED "\e[0;91m"
# define HGREEN "\e[0;92m"
# define HYELLOW "\e[0;93m"
# define HBLUE "\e[0;94m"
# define HMAGENTA "\e[0;95m"
# define HCYAN "\e[0;96m"
# define HWHITE "\e[0;97m"

/*
** Bold high intensity text
*/
# define BHBLACK "\e[1;90m"
# define BHRED "\e[1;91m"
# define BHGREEN "\e[1;92m"
# define BHYELLOW "\e[1;93m"
# define BHBLUE "\e[1;94m"
# define BHMAGENTA "\e[1;95m"
# define BHCYAN "\e[1;96m"
# define BHWHITE "\e[1;97m"

/*
** Reset (default color)
*/
# define RESET "\e[0m"
#endif
