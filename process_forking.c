/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_forking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:36:02 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/01 17:05:26 by acourtar         ###   ########.fr       */
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

// creates full pathnames to the file we're looking for by 
// copying the contents of dir and file into the previously allocated
// memory of goal.
// If the user specified a full path, just check that instead.
static void	create_path(char *goal, char *dir, char *file, int *pathav)
{
	int	i;
	int	len;

	if (dir == NULL || ft_strchr(file, '/') != NULL)
	{
		len = ft_strlen(file);
		ft_memcpy(goal, file, len + 1);
		*pathav = -1;
		return ;
	}
	i = 0;
	len = ft_strlen(dir);
	ft_memcpy(goal, dir, len);
	i = len;
	goal[i] = '/';
	len = ft_strlen(file);
	ft_memcpy(goal + i + 1, file, len + 1);
}

static void	build_path(char *goaldir, char **execargs, t_data *dat)
{
	int	i;

	i = 0;
	while (dat->pathav == 1 && dat->pathdir[i] != NULL)
	{
		create_path(goaldir, dat->pathdir[i], execargs[0], &(dat->pathav));
		execve(goaldir, execargs, dat->envp);
		i++;
	}
	if (dat->pathav == 0)
	{
		create_path(goaldir, NULL, execargs[0], &(dat->pathav));
		execve(goaldir, execargs, dat->envp);
	}
}

static void	child_process(int f1, int pipefd[2], t_data *dat)
{
	char	*goaldir;

	close(pipefd[0]);
	dup2(f1, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	goaldir = malloc(dat->maxpathlen);
	if (goaldir == NULL)
		exit_func();
	build_path(goaldir, dat->execargs1, dat);
	if (dat->pathav == -1)
		ft_printf_err("%s: %s: No such file or directory", \
		dat->argv[0], dat->argv[2]);
	else
		ft_printf_err("%s: %s: command not found\n", \
		dat->argv[0], dat->argv[2]);
	exit(EXIT_FAILURE);
}

static void	parent_process(int f2, int pipefd[2], int childpid, t_data *dat)
{
	char	*goaldir;

	waitpid(-1, &childpid, 0);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	close(pipefd[0]);
	goaldir = malloc(dat->maxpathlen);
	if (goaldir == NULL)
		exit_func();
	build_path(goaldir, dat->execargs2, dat);
	if (dat->pathav == -1)
		ft_printf_err("%s: %s: No such file or directory", \
		dat->argv[0], dat->argv[3]);
	else
		ft_printf_err("%s: %s: command not found\n", \
		dat->argv[0], dat->argv[3]);
	exit(EXIT_FAILURE);
}

void	cmd_exec(int origfd[2], int pipefd[2], t_data *dat)
{
	int	forkpid;

	forkpid = 0;
	if (dat->err[0] == 0 && dat->err[1] == 0)
	{
		forkpid = fork();
		if (forkpid < 0)
		{
			perror("");
			exit_func();
		}
		if (forkpid == 0)
			child_process(origfd[0], pipefd, dat);
		parent_process(origfd[1], pipefd, forkpid, dat);
	}
	else if (dat->err[1] == 0)
		parent_process(origfd[1], pipefd, forkpid, dat);
	else if (dat->err[0] == 0)
		child_process(origfd[0], pipefd, dat);
}
