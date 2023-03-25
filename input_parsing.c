/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:38:12 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/25 14:47:29 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>		// pipe(), close(), read(), execve(), dup2()
#include <fcntl.h>		// open()
#include <stdlib.h>		// exit()
#include <sys/wait.h>	// wait()
#include <stdio.h>		// printf(), perror()

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

void	create_path(char *goal, char *dir, char *file)
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
