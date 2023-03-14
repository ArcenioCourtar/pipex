/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:32:49 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/19 09:30:25 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// malloc() nelem * elsize bytes and set them all to 0.
void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*array;

	array = malloc(nelem * elsize);
	if (array == NULL)
		return (NULL);
	ft_bzero(array, (nelem * elsize));
	return (array);
}
