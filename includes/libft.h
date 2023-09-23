/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:20:44 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 18:29:05 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "ft_printf.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				ft_putstr_fd(char *s, int fd);
char				*ft_strjoin(char *tmp, char *buf);
/*
 *	Makes integer from string, skiping all the whitespaces
 *	if minus symbol is in the string, number will be negative
*/
int					ft_atoi(const char *nptr);
/*
 *	Makes {n} values of pointer {s} equal to zero
*/
void				ft_bzero(void *s, size_t n);
/*
 *	Allocates the requested memory and returns a pointer to it.
 *	Sets allocated memory to zero.
*/
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
/*
 *	Makes string representation of the number,
 * 	allocates memory for the string and returns it. 
*/
char				*ft_itoa(int n);
/*
 *	 Adds the node ’new’ at the end of the list.
*/
void				ft_lstadd_back(t_list **lst, t_list *new);
/*
 *	 Adds the node ’new’ at the beginning of the list.
*/
void				ft_lstadd_front(t_list **lst, t_list *new);
/*
 *	Deletes and frees the given node and every
 *	successor of that node, using the function ’del’ and free().
 *	The pointer to the list must be set to NULL.
*/
void				ft_lstclear(t_list **lst, void (*del)(void *));

/*
 *	Takes as a parameter a node and frees the memory of
 *	the node’s content using the function ’del’ given
 *	as a parameter and free the node. The memory of
 *	’next’ must not be freed.
*/
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
/*
 *	Iterates the list ’lst’ and applies the function
 *	’f’ on the content of each node. Creates a new
 *	list resulting of the successive applications of
 *	the function ’f’. The ’del’ function is used to
 *	delete the content of a node if memory allocations falls.
*/
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
/*
 *	Allocates with malloc() and returns a new node.
 *	The member variable {content} is initialized with
 *	the value of the parameter {content}. The variable
 *	{next} is initialized to NULL.
*/
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
/*
 *	Searches for the first occurrence of the character {c} (an unsigned char) 
 *	in the first {n} bytes of the string pointed to, by the argument {str}.
*/
void				*ft_memchr(const void *s, int c, size_t n);
/*
 *	Compares the first n bytes of memory area {s1} and memory area {s2}.
 * 	Returns difference of first bytes that differ as {str1[i] - str2[i]}
*/
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
/*
 *	Allocates with malloc() and returns an array
 *	of strings obtained by splitting {s} using the
 *	character {c} as a delimiter. The array must end
 *	with a NULL pointer.
*/
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
// char	*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
/*
 *	Allocates (with malloc(3)) and returns a substring
 *	from the string ’s’.
 *	The substring begins at index ’start’ and is of
 *	maximum size ’len’.
*/
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);

#endif