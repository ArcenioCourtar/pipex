/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:01:20 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/14 18:13:42 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>	// pipe(), close(), read()
#include <fcntl.h>	// open()

int	main(int argc, char **argv)
{
	int		pipefd[2];
	char	buffer[10000];

	if (argc != 5)
		return (0);
	ft_bzero(buffer, 10000);
	pipefd[0] = open(argv[1], O_RDONLY);
	pipefd[1] = open(argv[4], O_WRONLY);
	read(pipefd[0], buffer, 9999);
	ft_printf("%s\n", buffer);
}
