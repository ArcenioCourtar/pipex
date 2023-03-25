/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:01:20 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/25 19:48:20 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>		// pipe(), close(), read(), execve(), dup2()
#include <fcntl.h>		// open()
#include <stdlib.h>		// exit()
#include <sys/wait.h>	// wait()
#include <stdio.h>		// printf(), perror()

// Checks if the 4 additional args are present. If not, exit().
static void	check_args(int argc)
{
	if (argc != 5)
	{
		write(STDOUT_FILENO, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38);
		exit(EXIT_SUCCESS);
	}
}

/*
Main function:

First counts the # of arguments.
Then set up the struct that contains the data pertaining the files, 
shell commands, and environment variables.
Sets up file descriptors.
Finally forks if necessary (does not fork if the input file is not found).
Perform some pipe magic.
*/
int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	int		origfd[2];
	int		pidstat;
	t_data	*data;

	check_args(argc);
	data = build_struct(argv, envp);
	// protection
	if (openfd(origfd, pipefd, data) == 1)
		pidstat = fork();
	else
		pidstat = 1;
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
