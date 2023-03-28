/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:45:57 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/28 16:46:58 by acourtar         ###   ########.fr       */
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

void	access_open(t_data *data)
{
	int	acc_result;

	acc_result = access(data->argv[1], R_OK);
	if (acc_result < 0)
		data->err[0] = errno;
	acc_result = access(data->argv[4], W_OK);
	if (acc_result < 0)
		data->err[1] = errno;
}

void	fd_setup(int origfd[2], int pipefd[2], t_data *data)
{
	pipe(pipefd);
	if (data->err[0] != 0)
		ft_printf("Infile: %s\n", strerror(data->err[0]));
	else
		origfd[0] = open(data->argv[1], O_RDONLY);
	if (data->err[1] == EACCES)
		ft_printf("Outfile: %s\n", strerror(data->err[1]));
	else if (data->err[1] == ENOENT)
	{
		origfd[1] = open(data->argv[4], O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		data->err[1] = 0;
	}
	else
		origfd[1] = open(data->argv[4], O_WRONLY | O_TRUNC);
}