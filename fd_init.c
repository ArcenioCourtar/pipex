/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:45:57 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/05 12:07:23 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <string.h>		// strerror()
#include <unistd.h>		// pipe(), close(), read(), execve(), dup2()
#include <fcntl.h>		// open()
#include <stdlib.h>		// exit()
#include <sys/wait.h>	// wait()
#include <stdio.h>		// printf(), perror()
#include <errno.h>		// errno

void	access_open(t_data *dat)
{
	int	acc_result;

	acc_result = access(dat->argv[1], R_OK);
	if (acc_result < 0)
		dat->err[0] = errno;
	acc_result = access(dat->argv[4], W_OK);
	if (acc_result < 0)
		dat->err[1] = errno;
}

void	fd_setup(int origfd[2], t_data *dat)
{
	if (dat->err[0] != 0)
		ft_printf_err("%s: %s: %s\n", dat->argv[0], dat->argv[1], \
		strerror(dat->err[0]));
	else
		origfd[0] = open(dat->argv[1], O_RDONLY);
	if (dat->err[1] == EACCES)
		ft_printf_err("%s: %s: %s\n", dat->argv[0], dat->argv[4], \
		strerror(dat->err[1]));
	else if (dat->err[1] == ENOENT)
	{
		origfd[1] = open(dat->argv[4], O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dat->err[1] = 0;
	}
	else
		origfd[1] = open(dat->argv[4], O_WRONLY | O_TRUNC);
}
