/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_forking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:36:02 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/08 16:44:46 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>		// pipe(), close(), dup2(), fork()
#include <stdlib.h>		// malloc(), exit()
#include <sys/wait.h>	// waitpid()
#include <stdio.h>		// perror()
#include <errno.h>		// errno

// Child process that handles the input file.
// Tweaked error messages from default perror() results to match bash.
static void	child_in(int f1, int pipefd[2], t_data *dat)
{
	char	*goaldir;

	if (close(pipefd[0]) == -1)
		err_exit();
	if (dup2(f1, STDIN_FILENO) == -1 || dup2(pipefd[1], STDOUT_FILENO) == -1)
		err_exit();
	if (close(pipefd[1]) == -1 || close(f1) == -1)
		err_exit();
	goaldir = malloc(dat->maxpathlen);
	if (goaldir == NULL)
		err_exit();
	build_path(goaldir, dat->execargs1, dat);
	if (dat->pathav == -1)
		ft_printf_err("%s: %s: No such file or directory\n", \
		dat->argv[0], dat->argv[2]);
	else
		ft_printf_err("%s: %s: command not found\n", \
		dat->argv[0], dat->argv[2]);
	exit(EXIT_FAILURE);
}

// Child process that handles the output file
static void	child_out(int f2, int pipefd[2], t_data *dat)
{
	char	*goaldir;

	if (close(pipefd[1]) == -1)
		err_exit();
	if (dup2(pipefd[0], STDIN_FILENO) == -1 || dup2(f2, STDOUT_FILENO) == -1)
		err_exit();
	if (close(pipefd[0]) == -1 || close(f2) == -1)
		err_exit();
	goaldir = malloc(dat->maxpathlen);
	if (goaldir == NULL)
		err_exit();
	build_path(goaldir, dat->execargs2, dat);
	if (dat->pathav == -1)
		ft_printf_err("%s: %s: No such file or directory\n", \
		dat->argv[0], dat->argv[3]);
	else
		ft_printf_err("%s: %s: command not found\n", \
		dat->argv[0], dat->argv[3]);
	exit(EXIT_FAILURE);
}

// forking, and calling the appropriate child function, passed as parameter.
static void	child_creat(void (*childptr)(), int fd, int pipefd[2], t_data *dat)
{
	int	forkpid;

	forkpid = fork();
	if (forkpid < 0)
		err_exit();
	if (forkpid == 0)
		childptr(fd, pipefd, dat);
}

// Forking the appropriate amount of times based on the errors found previously
// Do not fork when the infile/outfile returned an unresolvable error earlier
// Reading from en empty pipe or writing to a pipe that no one reads from 
// does not result in any weird behaviour.
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

// Set up pipes, fork() the necessary child processes,
// close all fds (since the parent does not use them), wait for all children
// to terminate.
void	cmd_exec(int origfd[2], t_data *dat)
{
	int	child_count;
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		err_exit();
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
