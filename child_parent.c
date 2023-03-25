/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:41:01 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/25 14:41:13 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>		// pipe(), close(), read(), execve(), dup2()
#include <fcntl.h>		// open()
#include <stdlib.h>		// exit()
#include <sys/wait.h>	// wait()
#include <stdio.h>		// printf(), perror()

// TODO: check behavior if first exec is not found vs 2nd exec is not found
void	child_func(int pipefd[2], int f1, t_data *data)
{
	int		i;
	char	*goaldir;

	i = 0;
	close(pipefd[0]);
	ft_printf("child\n");
	dup2(f1, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	goaldir = malloc(data->maxpathlen);
	// protection
	while (data->pathdir[i] != NULL)
	{
		create_path(goaldir, data->pathdir[i], data->execargs1[0]);
		execve(goaldir, data->execargs1, data->envp);
		i++;
	}
	perror("");
	exit(EXIT_FAILURE);
}

void	parent_func(int pipefd[2], int f2, int child, t_data *data)
{
	int		i;
	char	*goaldir;

	i = 0;
	waitpid(-1, &child, 0);
	ft_printf("parent\n");
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	goaldir = malloc(data->maxpathlen);
	// protection
	while (data->pathdir[i] != NULL)
	{
		create_path(goaldir, data->pathdir[i], data->execargs2[0]);
		execve(goaldir, data->execargs2, data->envp);
		i++;
	}
	perror("");
	exit(EXIT_FAILURE);
}