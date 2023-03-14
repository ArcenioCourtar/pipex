/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:40:35 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/18 17:44:43 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// Converts the digits of integer 'n' to it's character equivalents
// and outputs them to file dscriptor 'fd' one by one.
void	ft_putnbr_fd(int n, int fd)
{
	char	result;
	long	n_long;

	n_long = (long)n;
	result = '0';
	if (n_long < 0)
	{
		n_long *= -1;
		write(fd, "-", 1);
	}
	if (n_long > 9)
	{
		ft_putnbr_fd((n_long / 10), fd);
	}
	result += n_long % 10;
	write(fd, &result, 1);
}
