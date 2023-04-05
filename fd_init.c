/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:45:57 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/05 13:52:19 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <string.h>		// strerror()
#include <unistd.h>		// access()
#include <fcntl.h>		// open()
#include <errno.h>		// errno

// Check file permissions. If the user does not have permissions to
// read/write that particular file, or the file does not exist, save the error
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

// Set up fds, and handle errors.
// If infile throws any error, print the approriate error.
// Same for outfile, except for ENOENT (file not found). In that case,
// silently create the output file.
void	fd_setup(int origfd[2], t_data *dat)
{
	if (dat->err[0] != 0)
		ft_printf_err("%s: %s: %s\n", dat->argv[0], dat->argv[1], \
		strerror(dat->err[0]));
	else
		origfd[0] = open(dat->argv[1], O_RDONLY);
	if (dat->err[1] == ENOENT)
	{
		origfd[1] = open(dat->argv[4], O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dat->err[1] = 0;
	}
	else if (dat->err[1] == 0)
		origfd[1] = open(dat->argv[4], O_WRONLY | O_TRUNC);
	else
		ft_printf_err("%s: %s: %s\n", dat->argv[0], dat->argv[4], \
		strerror(dat->err[1]));
}
