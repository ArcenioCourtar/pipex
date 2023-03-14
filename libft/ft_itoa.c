/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:39:28 by acourtar          #+#    #+#             */
/*   Updated: 2022/11/22 15:17:10 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

static int	numlen_calc(long n_long);

// Return newly allocated string equivalent to int 'n'.
char	*ft_itoa(int n)
{
	char	*str;
	long	n_long;
	int		numlen;

	if (n == 0)
		return (ft_strdup("0"));
	n_long = (long)n;
	numlen = numlen_calc(n_long);
	str = malloc(numlen + 1);
	if (str == NULL)
		return (NULL);
	if (n_long < 0)
	{
		n_long *= -1;
		str[0] = '-';
	}
	str[numlen] = '\0';
	while (n_long > 0)
	{
		numlen--;
		str[numlen] = '0' + (n_long % 10);
		n_long /= 10;
	}
	return (str);
}

// Calculate the length of the string resulting from the number given.
// Mostly important for malloc()ing the correct amount of bytes.
static int	numlen_calc(long n_long)
{
	int	numlen;

	if (n_long == 0)
		return (1);
	if (n_long < 0)
	{
		numlen = 2;
		n_long *= -1;
	}
	else
		numlen = 1;
	while (n_long > 9)
	{
		n_long = n_long / 10;
		numlen++;
	}
	return (numlen);
}
