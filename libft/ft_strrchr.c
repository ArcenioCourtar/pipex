/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:56:32 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/19 16:08:52 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// Looks through string 's' for character 'c'.
// Returns a pointer to last occurence of 'c' or NULL if 'c' is not found.
// SEE ALSO: ft_strchr().
char	*ft_strrchr(const char *s, int c)
{
	char	*i_ptr;
	char	*return_ptr;

	i_ptr = (char *) s;
	return_ptr = NULL;
	while (*i_ptr != '\0')
	{
		if (*i_ptr == (char)c)
			return_ptr = i_ptr;
		i_ptr++;
	}
	if (*i_ptr == (char)c)
		return_ptr = i_ptr;
	return (return_ptr);
}
