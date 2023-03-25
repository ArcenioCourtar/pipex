/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:01:20 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/25 15:45:29 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>		// pipe(), close(), read(), execve(), dup2()
#include <fcntl.h>		// open()
#include <stdlib.h>		// exit()
#include <sys/wait.h>	// wait()
#include <stdio.h>		// printf(), perror()

static void	check_args(int argc)
{
	if (argc != 5)
	{
		write(STDOUT_FILENO, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	int		origfd[2];
	int		pidstat;
	t_data	*data;

	check_args(argc);
	data = build_struct(argv, envp);
	// protection
	openfd(origfd, pipefd, data);
	pidstat = fork();
	if (pidstat < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	else if (pidstat == 0)
		child_func(pipefd, origfd[0], data);
	else
		parent_func(pipefd, origfd[1], pidstat, data);
	return (0);
}
