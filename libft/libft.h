/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:51:23 by alesanto          #+#    #+#             */
/*   Updated: 2020/02/04 19:16:39 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct			s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

typedef struct			s_parsing
{
	int					flagstiret;
	int					precision;
	char				*aff;
	int					flags0;
	int					c;
	int					w;
	int					z;
	int					neg;
}						t_parsing;

char					*ft_strtrim(char const *str, char const *set);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strmapi(char const *s,
							char (*f)(unsigned int, char));
int						ft_strlen(const char *str);
char					*ft_strjoin(char const *s1, char const *s2, int f);
char					*ft_strdup(const char *src);
char					**ft_split(const char *str, char c);
int						ft_atoi(const char *str);
char					*ft_itoa(int n);
void					ft_bzero(void *s, size_t n);
void					*ft_memset (void *b, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst,
							const void *src, int c, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t n);
int						ft_isdigit(int c);
int						ft_isalpha(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_tolower(int c);
int						ft_toupper(int c);
char					*ft_strnstr(const char *s1, const char *s2, size_t n);
char					*ft_substr(char const *s,
							unsigned int start, size_t len);
void					*ft_memccpy(void *dest, const void *src,
							int c, size_t n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *str, int fd);
void					ft_putendl_fd(char *str, int fd);
void					ft_putnbr_fd(int n, int fd);
char					*ft_strrchr(const char *s, int c);
char					*ft_strchr(const char *s, int c);
t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **alst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **alst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst,
							void (*f)(void *));
t_list					*ft_lstmap(t_list *lst,
							void *(*f)(void *), void (*del)(void *));
unsigned int			ft_strlcat(char *dest, const char *src, size_t size);
size_t					ft_strlcpy(char *dest, const char *src, size_t n);
void					*ft_calloc(size_t count, size_t size);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
int						get_next_line(int fd, char **line);
void					ft_strdel(char **str);
char					*ft_suprspace(char *str);
char					*ft_cjoin(char const *s1, char c, int f);
float					ft_fpower(float nb, int power);

/*
** ft_printf
*/

int						ft_printf(const char *format, ...);
int						ft_boucle(char *arg, va_list *va);
int						ft_parsingpf(char *arg,
							va_list *va, t_parsing *parsing);
void					ft_init_parsing(t_parsing *parsing);
void					ft_init_parsing(t_parsing *parsing);

int						ft_flags(char *arg, t_parsing *parsing);
int						ft_width(char *arg, va_list *va, t_parsing *parsing);
int						ft_width2(char *arg, t_parsing *parsing, int i);
int						ft_precision(char *arg,
							va_list *va, t_parsing *parsing);
int						ft_lenght(char *arg, t_parsing *parsing);

void					ft_flagsapp(t_parsing *parsing, char arg);
void					ft_s_precisionapp(char arg, t_parsing *parsing);
void					ft_precisionappnbr(t_parsing *parsing);
void					ft_app(char arg, t_parsing *parsing);
void					ft_exception(t_parsing *parsing, char arg);

char					*ft_ptoa_base(unsigned long long int nbr, char *base);
char					*ft_itoa_base(unsigned nbr, char *base);
char					*ft_strjoin_c(char const *s1, char c);
char					*ft_cdup(int c);
void					ft_flagsapp0(t_parsing *parsing, char arg);

int						ft_putstr_pf(char *str, int fd);

#endif
