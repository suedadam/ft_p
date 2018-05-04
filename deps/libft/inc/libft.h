/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 22:58:39 by satkins           #+#    #+#             */
/*   Updated: 2018/04/20 12:59:07 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>

# define BUFF_SIZE 2048

# define ABS(X) X > 0 ? X : -X
# define IS_WHITESPACE(c) (is_whitespace(c))

int					g_fd;

typedef struct		s_errno
{
	int			ernum;
	char		*reason;
}					t_errno;

typedef struct		s_meta
{
	size_t		len;
}					t_meta;

typedef struct		s_chunk
{
	int		fd;
	char	*str;
}					t_chunk;

typedef struct		s_btree
{
	void			*data;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_node
{
	void			*content;
	struct s_node	*next;
	struct s_node	*previous;
}					t_node;

typedef struct		s_dblist
{
	t_node			*first;
	t_node			*last;
	int				nbr_elements;
}					t_dblist;

typedef struct		s_pqueue
{
	t_node			*first;
}					t_pqueue;

typedef struct		s_stack
{
	t_node			*top;
}					t_stack;

typedef struct		s_queue
{
	t_node			*first;
	t_node			*last;
}					t_queue;

typedef struct		s_index
{
	int				y;
	int				x;
}					t_index;

t_node				*new_node(void);
char				*ft_strerror(int num);

/*
** Tracked memory allocations.
*/

void				*meta_malloc(size_t size);
void				*meta_realloc(void *old, size_t newsize);
void				meta_free(void *old);

/*
** Stack
*/
void				*ft_stackpeak(t_stack *stack);
void				*ft_stackpop(t_stack *stack);
int					ft_stackpush(t_stack *stack, void *content, size_t c_size);
t_stack				*new_stack(void);
int					isempty_stack(t_stack *stack);

/*
** Double linked list
*/
t_dblist			*new_dblist(void);
int					dbl_push_end(t_dblist *dblist, void *content,
						size_t c_size);
int					dbl_push_front(t_dblist *dblist, void *content,
						size_t c_size);
int					isempty_dblist(t_dblist *dblist);

/*
** Priority Queue
*/
void				ft_enpqueue(t_pqueue *queue, void *content, size_t c_size,
					int (*comparer)(void *, void *));
void				*peek_pqueue(t_pqueue *queue);
void				*ft_depqueue(t_pqueue *queue);
t_pqueue			*init_pqueue(void);
void				del_pqueue(t_pqueue *queue, void (*deconstruct)(void *ptr));

/*
** Queue
*/
t_queue				*new_queue(void);
int					ft_enqueue(t_queue *queue, void *content, size_t c_size);
void				*ft_dequeue(t_queue *queue);
void				*peek_queue(t_queue *queue);
int					isempty_queue(t_queue *queue);

/*
** Libft
*/
uint8_t				is_whitespace(char c);
void				ft_bzero(void *s, size_t n);
size_t				ft_printf(char *format, ...);
size_t				ft_printf_fd(int fd, char *format, ...);
int					get_next_line(int fd, char **line);
void				*ft_memset(void *b, int c, size_t len);
int					ft_atoi(const char *str);
long long			ft_atoll(const char *str);
int					ft_isalpha(int c);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strrchr(const char *s, int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strstr(const char *big, const char *little);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnjoin(char const *s1, char const *s2, int i);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
size_t				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnstr(char *str, int len);
void				ft_putnstr_fd(char *str, int len, int fd);
void				handle_error(void);
void				ft_toupper_str(char *str);
char				*ft_ullitoa_base(unsigned long long int num, int base);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *newl);
int					is_numstr(char *line);
int					ft_strcmp_wlen(const char *str1, const char *str2);
void				ft_lstappend(t_list **head, t_list *newl);
void				del_node(t_node *node, t_node *prev);
char				**ft_splitwhitespace(char const *s);

#endif
