/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:07:23 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/17 15:52:41 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

typedef struct s_list {
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

// ft_printf functions
int		ft_printf(char *format, ...);
int		ft_print_chr(int c);
int		ft_print_str(char *str);
int		ft_print_nbr(int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex(unsigned int n, char c);
int		ft_print_ptr(uintptr_t nbr);
int		ft_print_pct(void);
char	*convert_to_hexa(unsigned long nbr);
// get_next_line functions
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strchr(char *s, int c);
char	*gnl_strdup(char *s1);
char	*get_next_line(int fd, int err);
size_t	gnl_strlcpy(char *dst, char *src, size_t dstsize);
// libft part 1
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_memcmp(void *s1, void *s2, size_t n);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
long	ft_atoi(char *str);
char	*ft_strdup(char *s1);
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memchr(void *s, int c, size_t n);
void	*ft_memmove(void *dst, void *src, size_t len);
void	*ft_memcpy(void *dst, void *src, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, char *src,
			size_t dstsize);
// part 2
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	**ft_split(char *s, char c);
char	**ft_free_split(char **tab);
char	*ft_itoa(int n);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strndup(const char *str, int nb);
// error
void	ft_error(char *msg);
void	ft_free_all(char **arr);
// t_list
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
// sort
void	ft_advanced_sort_string_tab(char **tab,
	int (*cmp)(const char *, const char *));
#endif
