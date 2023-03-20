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
	char	*args[] = {"cat", "infile", NULL};

	f1 = f1 + 0;
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	execve("/bin/cat", args, NULL);
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

void	parent_func(int pipefd[2], int f2, int child)
{
	static char	buf[10000] = {0};

	f2 = f2 + 0;
	close(pipefd[1]);
	waitpid(-1, &child, 0);
	read(pipefd[0], buf, 10000);
	write(f2, buf, ft_strlen(buf));
	close(pipefd[0]);
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
