/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:10:09 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/28 12:46:19 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <wchar.h>
# include <stdbool.h>

// # define MAX(A, B) (A > B ? A : B)
// # define MIN(A, B) (A > B ? B : A)

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

//  Part 1 

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_atoi(const char *nptr);

size_t		ft_strlen(const char *s);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strchr(const char *s, int c);
bool		ft_strchr_bool(const char *str, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char	*big, const char *little, size_t len);
char		*ft_strdup(const char *str);
char		*ft_strndup(const char *str, size_t n);

void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_calloc(size_t number, size_t size);
void		*ft_realloc(void *ptr, size_t new_size);

// Part 2 

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

// Bonus Part 

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
int			ft_lstsize(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *newlist);
void		ft_lstadd_back(t_list **lst, t_list *newlist);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// Extra Functions

int			ft_min(int a, int b);
int			ft_max(int a, int b);
int			ft_abs(int a);

// Get next line

void		add_to_stash(t_list **lst, char *buf, int readed);
void		read_and_stach(int fd, t_list **lst);
int			found_newline(t_list *lst);
char		*get_next_line(int fd, char **line);
void		free_stash(t_list **lst, int type_clean);
t_list		*ft_lstlast(t_list *lst);
char		*generate_line(t_list *lst);
char		*extract_line(t_list *lst);
void		clean_stash(t_list **lst);

size_t		ft_wdcount(const char *str, char delimiter);
int			ft_printf(const char *format, ...);

#endif