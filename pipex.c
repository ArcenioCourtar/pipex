/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:14:06 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/05 12:27:43 by acourtar         ###   ########.fr       */
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

void	check_args(int argc)
{
	if (argc != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		origfd[2];
	t_data	*dat;	

	check_args(argc);
	dat = build_struct(argv, envp);
	access_open(dat);
	fd_setup(origfd, dat);
	cmd_exec(origfd, dat);
	return (0);
}
