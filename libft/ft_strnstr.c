/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:32:17 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/24 13:05:34 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static int	compare(const char *big, const char *little, size_t len);

// Searches for the string 'little' inside of 'big' for 'len' characters.
// Returns a pointer to the first character of 'little' within 'big' if found.
// If 'little' is empty, returns 'big'. If 'little' is not found, NULL.
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *) big);
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			if (compare(big + i, little, len - i) == 1)
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

// Compares section of 'big' to the entirety of 'little'
static int	compare(const char *big, const char *little, size_t len)
{
	unsigned int	i;

	i = 0;
	while (little[i] != '\0' && i < len)
	{
		if (big[i] == little[i])
			i++;
		else
			return (0);
	}
	if (little[i] == '\0')
		return (1);
	return (0);
}
