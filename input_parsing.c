/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:38:12 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/25 17:09:24 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>		// pipe(), close(), read(), execve(), dup2()
#include <fcntl.h>		// open()
#include <stdlib.h>		// exit()
#include <sys/wait.h>	// wait()
#include <stdio.h>		// printf(), perror()

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

char	**create_touch_args(t_data *data)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc(sizeof(char *) * 3);
	// protection
	new[0] = ft_strdup("touch");
	new[1] = ft_strdup(data->argv[4]);
	new[2] = NULL;
	return (new);
}

// TODO: if infile doesn't exist prevent program from waiting for user input.
// TODO: use $PATH to construct goal directory?
void	openfd(int origfd[2], int pipefd[2], t_data *data)
{
	int		touchpid;
	char	**touchargs;

	origfd[0] = open(data->argv[1], O_RDONLY);
	origfd[1] = open(data->argv[4], O_WRONLY);
	if (origfd[1] < 0)
	{
		touchargs = create_touch_args(data);
		touchpid = fork();
		if (touchpid == 0)
			execve("/usr/bin/touch", touchargs, data->envp);
		waitpid(-1, &touchpid, 0);
		origfd[1] = open(data->argv[4], O_WRONLY);
	}
	if (origfd[0] < 0)
	{
		perror("");
	}
	if (pipe(pipefd) == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
}
