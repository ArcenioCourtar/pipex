/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_forking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:36:02 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/28 16:47:36 by acourtar         ###   ########.fr       */
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
static void	create_path(char *goal, char *dir, char *file)
{
	int	i;
	int	len;

	if (ft_strchr(file, '/') != NULL)
	{
		len = ft_strlen(file);
		ft_memcpy(goal, file, len + 1);
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

static void	child_process(int f1, int pipefd[2], t_data *data)
{
	int		i;
	char	*goaldir;

	close(pipefd[0]);
	dup2(f1, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	goaldir = malloc(data->maxpathlen);
	if (goaldir == NULL)
		exit_func();
	i = 0;
	while (data->pathdir[i] != NULL)
	{
		create_path(goaldir, data->pathdir[i], data->execargs1[0]);
		execve(goaldir, data->execargs1, data->envp);
		i++;
	}
	perror("");
	exit(EXIT_FAILURE);
}

static void	parent_process(int f2, int pipefd[2], int childpid, t_data *data)
{
	int		i;
	char	*goaldir;

	waitpid(-1, &childpid, 0);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	close(pipefd[0]);
	goaldir = malloc(data->maxpathlen);
	if (goaldir == NULL)
		exit_func();
	i = 0;
	while (data->pathdir[i] != NULL)
	{
		create_path(goaldir, data->pathdir[i], data->execargs2[0]);
		execve(goaldir, data->execargs2, data->envp);
		i++;
	}
	perror("");
	exit(EXIT_FAILURE);
}

void	cmd_exec(int origfd[2], int pipefd[2], t_data *data)
{
	int	forkpid;

	if (data->err[0] == 0 && data->err[1] == 0)
	{
		forkpid = fork();
		if (forkpid == 0)
			child_process(origfd[0], pipefd, data);
		parent_process(origfd[1], pipefd, forkpid, data);
	}
	else if (data->err[1] == 0)
		parent_process(origfd[1], pipefd, forkpid, data);
	else if (data->err[0] == 0)
		child_process(origfd[0], pipefd, data);
}
