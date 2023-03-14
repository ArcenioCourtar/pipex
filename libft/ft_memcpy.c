/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:33:07 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/19 15:33:21 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// Copies 'n' bytes from 'src' to 'dest'.
// DOES NOT CHECK IF THE AREAS OVERLAP. IF THEY MIGHT USE ft_memmove().
// Original function segfaults if either of the addresses is NULL,
// but not if both are NULL
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*dest_start;

	dest_start = dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n > 0)
	{
		*(char *) dest = *(char *) src;
		n--;
		dest++;
		src++;
	}
	return (dest_start);
}
