/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:38:12 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/26 15:24:17 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>		// pipe(), close(), read(), execve(), dup2()
#include <fcntl.h>		// open()
#include <stdlib.h>		// exit()
#include <sys/wait.h>	// wait()
#include <stdio.h>		// printf(), perror()
#include <errno.h>		// errors

// creates full pathnames to the file we're looking for by 
// copying the contents of dir and file into the previously allocated
// memory of goal.
// If the user specified a full path, just check that instead.
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

// argument parsing for the execve() call for touch.
char	**create_touch_args(t_data *data)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc(sizeof(char *) * 3);
	if (new == NULL)
		exit_func(NULL, NULL);
	new[0] = ft_strdup("touch");
	if (new[0] == NULL)
		exit_func(NULL, NULL);
	new[1] = ft_strdup(data->argv[4]);
	if (new[1] == NULL)
		exit_func(NULL, NULL);
	new[2] = NULL;
	return (new);
}

void	open_checkacc(int origfd[2], t_data *data)
{
	origfd[0] = open(data->argv[1], O_RDONLY);
	origfd[1] = open(data->argv[4], O_WRONLY);
}

// TODO: use $PATH to construct goal directory?
// Sets up pipe, and opens fds for the infile and outfile.
// If the specified outfile does not exist, create it.
// If the infile does not exist, print an error message and don't create
// the child process in the main function.
int	openfd(int origfd[2], int pipefd[2], t_data *data)
{
	int		touchpid;
	char	**touchargs;

	open_checkacc(origfd, data);
	if (pipe(pipefd) == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
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
		return (0);
	}
	return (1);
}
