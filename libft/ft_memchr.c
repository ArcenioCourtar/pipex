/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:31:40 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/19 09:35:23 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// Scans the intial 'n' bytes starting from memory address 's'
// for the first instance of 'c'.
// Returns pointer to 'c' or NULL if 'c' is not found.
// SEE ALSO: ft_strchr() for the same operation on just strings.
void	*ft_memchr(const void *s, int c, size_t n)
{
	const void		*ptr;
	unsigned char	val;

	val = (unsigned char)c;
	ptr = s;
	while (n > 0)
	{
		if (*(unsigned char *)ptr == val)
			return ((void *)ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
