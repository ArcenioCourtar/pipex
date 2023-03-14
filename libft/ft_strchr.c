/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:56:29 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/19 16:08:45 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// Looks through string 's' for character 'c'.
// Returns a pointer to first occurence of 'c' or NULL if 'c' is not found.
// SEE ALSO: ft_memchr() & ft_strrchr().
char	*ft_strchr(const char *s, int c)
{
	char	*i_ptr;

	i_ptr = (char *) s;
	while (*i_ptr != '\0')
	{
		if (*i_ptr == (char)c)
			return (i_ptr);
		i_ptr++;
	}
	if (*i_ptr == (char)c)
		return (i_ptr);
	return (NULL);
}
