/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:38:37 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/05 12:45:47 by acourtar         ###   ########.fr       */
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

void	build_path(char *goaldir, char **execargs, t_data *dat)
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
