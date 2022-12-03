/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:01:40 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/08/27 16:55:50 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include	<stdlib.h>
# include	<string.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int a);
int		ft_isdigit(int a);
int		ft_isalnum(int a);
int		ft_isascii(int a);
int		ft_isprint(int a);
size_t	ft_strlen(const char *string);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy( void *desti, const void *original, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int letter);
int		ft_tolower(int letter);
char	*ft_strchr(const char *string, int letter);
int		ft_strncmp( const char *str1, const char *str2, int n );
void	*ft_memchr(const void *str, int chr, size_t len);
int		ft_memcmp( const void *ptr1, const void *ptr2, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strdup(const char *str);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t max_len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int num);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//get next line 
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

int		lookfor(int fd, char *buffer, char *tmp_buf);
char	*get_next_line(int fd);

//ft_print
static const char	g_char_str[] = "0123456789abcdefghjklmonpqrstuvwxyz";
static const char	g_char_str_c[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char	g_hash[] = "0x";
static const char	g_hash_c[] = "0X";
static const char	g_null[] = "(null)";

//struct that store flags and string related values
typedef struct s_arg
{
	char	num[64];
	char	dta_typ;
	char	*dta_str;
	int		dta_len;
	int		width;
	char	wth_chr;
	int		precision;
	char	sign;
	char	side;
	char	hash;
	char	*out_str;
	int		max_len;
	int		output;
	int		total_length;
}			t_arg;

//sturcture that store typedependig data
typedef struct s_type
{
	size_t		cast;
	const char	*fix_str;
	int			fix_len;
	void		(*f_len)(t_arg *input);
	const char	*hash_str;
	int			hash_len;
	int			base;
	const char	*base_str;
}t_type;

void	calc_width( t_arg *input, t_type *type);
void	create_str( t_arg *input, t_type *type);
char	*my_strlchr(char *dst, const char c, int n);
void	fill_str( t_arg *input, t_type *type);
void	print_struct( t_arg *input);
char	*fill_list(char *str, struct s_arg *input, va_list va_ptr);
int		lenght_to_pcnt(char *str);
char	*my_putstring_length(t_arg *input, char *str, int n);
char	search_typ(const char *str, t_arg *input);
char	*convert_to_str(const char *str, void *ptr, t_arg *list);
int		ft_printf(const char *str, ...);
void	set_default(t_arg *input);
void	convert_num_to_str(t_arg *input, t_type *type);

//Funktion for calc the length of the input string depending on type
void	f_str_len(struct s_arg *input);
void	f_c_len(struct s_arg *input);
void	f_int_len(struct s_arg *input);

//Funktion that set some value depending on the type
void	setter_setter(t_arg *input, t_type *type, va_list va_ptr);
void	f_setter_u(t_type *type, va_list va_ptr);
void	f_setter_i(t_type *type, t_arg *input, va_list va_ptr);
void	f_setter_x(t_type *type, va_list va_ptr, char dta_typ);
void	f_setter_p(t_type *type, va_list va_ptr);
void	f_setter_o(t_type *type, va_list va_ptr);

#endif
