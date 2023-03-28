/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:14:06 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/28 16:45:30 by acourtar         ###   ########.fr       */
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

void	exit_func(void)
{
	exit(EXIT_FAILURE);
}

void	check_args(int argc)
{
	if (argc != 5)
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		origfd[2];
	int		pipefd[2];
	t_data	*data;	

	check_args(argc);
	data = build_struct(argv, envp);
	access_open(data);
	fd_setup(origfd, pipefd, data);
	cmd_exec(origfd, pipefd, data);
}
