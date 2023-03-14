/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:05:05 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/19 09:32:21 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

// ft_memset() but everything is zero instead of whatever byte value you want.
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
