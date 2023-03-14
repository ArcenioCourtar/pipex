/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:32:39 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/18 17:43:09 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// Outputs character 'c' to the given file descriptor 'fd'.
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
