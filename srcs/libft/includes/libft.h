/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:54:15 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/03/16 11:34:13 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

// LIBFT

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
size_t				ft_strlen(const char *str);
void				*ft_memset(void *ptr, int value, size_t count);
void				*ft_bzero(void *ptr, size_t count);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
unsigned int		ft_strlcat(char *dest, char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(char *s1, char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t n);
int					ft_atoi(const char *nptr);
long				ft_strtol(const char *nptr, char **endptr, int base);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *str);
char				*ft_strndup(const char *s, size_t n);

int					ft_is_string_number(char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char *str);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

char				**ft_splitdup(const char **src);
size_t				ft_splitlen(const char **src);
char				*ft_read(int fd);
char				*ft_strjoin_free(char **s1, char *s2);
char				*ft_strjoin_ff(char **s1, char *s2);
int					ft_ischarin(char c, char *str);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_free_matrix(unsigned int count, ...);
void				ft_free(unsigned int count, ...);
char				**ft_splitjoin(char **split, char *need_to_add_to_split);
char				**ft_splittrim(char **split, char *set);
void				ft_putsplit(char **split, char *message_before);
char				*ft_strjoinchar_free(char **s1, char s2);
void				ft_null(unsigned int count, ...);

// PRINTF
int					ft_printf(const char *format, ...);
int					ft_printf_fd(int fd, const char *format, ...);

int					ft_putchar_fd_l(char c, int fd);
int					ft_putstr_fd_l(char *s, int fd);
int					ft_putnbr_fd_l(int n, int fd);
int					ft_u_putnbr_fd_l(unsigned int n, int fd);
int					ft_hexadecimal(unsigned int x, char a, int fd);
int					ft_pointer(size_t x, int fd);

// GNL
char				*get_next_line(int fd);

#endif
