/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_forking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:36:02 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/05 12:54:27 by acourtar         ###   ########.fr       */
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

static void	child_in(int f1, int pipefd[2], t_data *dat)
{
	char	*goaldir;

	close(pipefd[0]);
	dup2(f1, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	goaldir = malloc(dat->maxpathlen);
	if (goaldir == NULL)
		exit(EXIT_FAILURE);
	build_path(goaldir, dat->execargs1, dat);
	if (dat->pathav == -1)
		ft_printf_err("%s: %s: No such file or directory", \
		dat->argv[0], dat->argv[2]);
	else
		ft_printf_err("%s: %s: command not found\n", \
		dat->argv[0], dat->argv[2]);
	exit(EXIT_FAILURE);
}

static void	child_out(int f2, int pipefd[2], t_data *dat)
{
	char	*goaldir;

	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	close(pipefd[0]);
	goaldir = malloc(dat->maxpathlen);
	if (goaldir == NULL)
		exit(EXIT_FAILURE);
	build_path(goaldir, dat->execargs2, dat);
	if (dat->pathav == -1)
		ft_printf_err("%s: %s: No such file or directory", \
		dat->argv[0], dat->argv[3]);
	else
		ft_printf_err("%s: %s: command not found\n", \
		dat->argv[0], dat->argv[3]);
	exit(EXIT_FAILURE);
}

static void	child_creat(void (*childptr)(), int fd, int pipefd[2], t_data *dat)
{
	int	forkpid;

	forkpid = fork();
	if (forkpid < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (forkpid == 0)
	{
		childptr(fd, pipefd, dat);
	}
}

static int	child_counter(int origfd[2], int pipefd[2], t_data *dat)
{
	if (dat->err[0] == 0 && dat->err[1] == 0)
	{
		child_creat(&child_in, origfd[0], pipefd, dat);
		child_creat(&child_out, origfd[1], pipefd, dat);
		return (2);
	}
	else if (dat->err[0] == 0)
	{
		child_creat(&child_in, origfd[0], pipefd, dat);
		return (1);
	}
	else if (dat->err[1] == 0)
	{
		child_creat(&child_out, origfd[1], pipefd, dat);
		return (1);
	}
	return (0);
}

void	cmd_exec(int origfd[2], t_data *dat)
{
	int	child_count;
	int	pipefd[2];

	pipe(pipefd);
	child_count = child_counter(origfd, pipefd, dat);
	close(pipefd[0]);
	close(pipefd[1]);
	close(origfd[0]);
	close(origfd[1]);
	while (child_count > 0)
	{
		waitpid(-1, NULL, 0);
		child_count--;
	}
}
