/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:10:12 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/24 12:18:33 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

// Concatenates 'dst' and 'src', the resulting string being at most
// 'size' bytes long and being stored in 'dst'.
// Returns the total length of the two original strings.
// Return value differs if 'size' == 0 or 'size' < strlen(dst).
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i_dst;
	unsigned int	i_src;
	unsigned int	initial_length;

	i_src = 0;
	initial_length = ft_strlen(dst) + ft_strlen(src);
	if (size == 0)
		return (ft_strlen(src));
	if (ft_strlen(dst) > size)
		return (ft_strlen(src) + size);
	i_dst = ft_strlen(dst);
	while (src[i_src] != '\0' && i_dst < size - 1)
	{
		dst[i_dst] = src[i_src];
		i_dst++;
		i_src++;
	}
	dst[i_dst] = '\0';
	return (initial_length);
}
