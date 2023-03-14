/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:15:15 by acourtar          #+#    #+#             */
/*   Updated: 2023/02/07 16:11:50 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>

// set the first n bytes starting from pointer s to byte c
void	*ft_memset(void *s, int c, size_t n);
// memset but with zero xddd
void	ft_bzero(void *s, size_t n);
// Create an array of nelem elements with byte size elsize
void	*ft_calloc(size_t nelem, size_t elsize);
// Copies n bytes from src to dest. MUST NO OVERLAP. Use memmove otherwise
void	*ft_memcpy(void *dest, const void *src, size_t n);
// Copies n bytes form src to dest, areas may overlap.
void	*ft_memmove(void *dest, const void *src, size_t n);
// Scans initial n bytes of memory for first instance of c. (interpr as uchar)
void	*ft_memchr(const void *s, int c, size_t n);
// Perform function 'f' on char 's'
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
// Outputs the character 'c' to the given file descriptor
void	ft_putchar_fd(char c, int fd);
// Outputs the string 's' to the given file descriptor
void	ft_putstr_fd(char *s, int fd);
// Outputs the string 's' to the given file decriptor followed by a newline
void	ft_putendl_fd(char *s, int fd);
// Outputs the integer 'n' to the given file descriptor
void	ft_putnbr_fd(int n, int fd);

// Returns 1 if character is part of the alphabet
int		ft_isalpha(int c);
// Returns 1 if character is a digit
int		ft_isdigit(int c);
// Returns 1 if character is a alphanumeric character
int		ft_isalnum(int c);
// Returns 1 if character is part of the ascii table (0 - 127 range)
int		ft_isascii(int c);
// Returns 1 if character is printable (space counts, tabs/newlines don't)
int		ft_isprint(int c);
// Returns 1 if character is " ", \t, \n, \f, \r, \v
int		ft_isspace(int c);
// does NOT change the param passed to it
int		ft_tolower(int c);
// does NOT change the param passed to it
int		ft_toupper(int c);
// Compares n bytes of s1 and s2 with each other, returns the difference
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// memcmp is strcmp without the str. xDDDDD
int		ft_memcmp(const void *s1, const void *s2, size_t n);
// Converts initial portion of string to an int
int		ft_atoi(const char *nptr);
// My 42 version of printf
int		ft_printf(const char *str, ...);
// Convert initial portion of string to a long
long	ft_atol(const char *str);

// Returns character length of the string (excluding the NULL-terminator!)
size_t	ft_strlen(const char *s);
// Copies string located in src into dst, up to size - 1 bytes
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
// Concatenates string in src to the string in dst up to size - bytes (combined)
size_t	ft_strlcat(char *dst, const char *src, size_t size);

// Find c in string s. Returns ptr to first instance of c, or NULL
char	*ft_strchr(const char *s, int c);
// Find c in string s. Returns ptr to last instance of c, or NULL
char	*ft_strrchr(const char *s, int c);
// Tries to find null-terminated string 'little' inside 'big'
char	*ft_strnstr(const char *big, const char *little, size_t len);
// Returns a pointer to a duplicate of string s, using malloc()
char	*ft_strdup(const char *s);
// Allocates and returns a substring from s, starting at start max size len
char	*ft_substr(char const *s, unsigned int start, size_t len);
// Allocates and returns a new string, a concatenation of s1 and s2
char	*ft_strjoin(char const *s1, char const *s2);
// Alloc+returns str, result of s1 being trimmed of first/last occurence of set
char	*ft_strtrim(char const *s1, char const *set);
// Returns a string representing the integer received (needs work)
char	*ft_itoa(int n);
// Perform function 'f' on char 's'. The result which gets saved to a new str
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
// Returns an 2d array of string by splitting pieces with character c
char	**ft_split(char const *s, char c);

// single direction linked list
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// Returns a new 't_list' with 'content' being the node's content
t_list	*ft_lstnew(void *content);
// Returns the last element in the list 'lst'
t_list	*ft_lstlast(t_list *lst);
// Iterates over all content starting from 'lst' and puts it in a new 'lst'
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// Adds the node 'new' to the end of the list 'lst'
void	ft_lstadd_back(t_list **lst, t_list *new);
// Adds the node 'new' to the front of the list 'lst'
void	ft_lstadd_front(t_list **lst, t_list *new);
// Applies function 'del()' to content and frees content, then frees lst node
void	ft_lstdelone(t_list *lst, void (*del)(void*));
// lstdelone() but for all nodes starting from 'lst'
void	ft_lstclear(t_list **lst, void (*del)(void*));
// Iterates over all list content starting from 'lst', with function 'f()'
void	ft_lstiter(t_list *lst, void (*f)(void *));

// Returns the number of nodes in the list 'lst'
int		ft_lstsize(t_list *lst);

#endif