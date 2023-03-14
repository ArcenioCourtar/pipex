/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:32:23 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/19 15:39:55 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// Compares the first 'n' bytes starting from 's1' to those starting from 's2'.
// Returns the value difference on the first byte that differs, of 0.
// SEE ALSO: ft_strncmp() for the same functionally on strings.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int			i;
	const char				*s1_tmp;
	const char				*s2_tmp;

	i = 0;
	s1_tmp = s1;
	s2_tmp = s2;
	if (n == 0)
		return (0);
	while (i < (n - 1))
	{
		if (s1_tmp[i] != s2_tmp[i])
			return ((unsigned char)s1_tmp[i] - (unsigned char)s2_tmp[i]);
		i++;
	}
	return ((unsigned char)s1_tmp[i] - (unsigned char)s2_tmp[i]);
}
