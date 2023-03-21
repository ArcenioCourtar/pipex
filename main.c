/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:01:20 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/20 18:39:53 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>		// pipe(), close(), read(), execve(), dup2()
#include <fcntl.h>		// open()
#include <stdlib.h>		// exit()
#include <sys/wait.h>	// wait()
#include <stdio.h>		// printf(), perror()

void	check_args(int argc)
{
	if (argc != 5)
	{
		write(STDOUT_FILENO, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38);
		exit(EXIT_SUCCESS);
	}
}

// TODO: if outfile does not currently exist, create it instead of
// printing errmsg
void	openfd(int origfd[2], int pipefd[2], char *argv[])
{
	origfd[0] = open(argv[1], O_RDONLY);
	origfd[1] = open(argv[4], O_WRONLY);
	if (origfd[0] < 0 || origfd[1] < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
}

void	child_func(int pipefd[2], int f1)
{
	char	*args[] = {"cat", NULL};

	close(pipefd[0]);
	dup2(f1, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execve("/bin/cat", args, NULL);
	perror("");
	exit(EXIT_FAILURE);
}

void	parent_func(int pipefd[2], int f2, int child)
{
	char	*args[] = {"/bin/ls", "-l", NULL};

	waitpid(-1, &child, 0);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	close(pipefd[0]);
	execve("/bin/ls", args, NULL);
	perror("");
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	int	pipefd[2];
	int	origfd[2];
	int	pidstat;

	check_args(argc);
	openfd(origfd, pipefd, argv);
	pidstat = fork();
	if (pidstat < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	else if (pidstat == 0)
		child_func(pipefd, origfd[0]);
	else
		parent_func(pipefd, origfd[1], pidstat);
	return (0);
}
