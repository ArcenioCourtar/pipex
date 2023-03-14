/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:33:46 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/19 15:34:32 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// ft_memcpy() but with memory location comparing.
// If the address of dest is higher than src it reverses copying order.
// This ensures whatever ends up in dest will be what was in src.
// This does NOT guarantee that src will not be different after.
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*dest_start;

	dest_start = dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (src < dest)
	{
		while (n > 0)
		{
			*(char *)(dest + n - 1) = *(char *)(src + n - 1);
			n--;
		}
	}
	else
	{
		while (n > 0)
		{
			*(char *) dest = *(char *) src;
			n--;
			dest++;
			src++;
		}
	}
	return (dest_start);
}
