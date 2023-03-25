/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:46:31 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/25 19:53:34 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>		// pipe(), close(), read(), execve(), dup2()
#include <fcntl.h>		// open()
#include <stdlib.h>		// exit()
#include <sys/wait.h>	// wait()
#include <stdio.h>		// printf(), perror()

// Finds the $PATH variable in the environment, 
// then puts all the possible PATHs in a list using ft_split
static char	**find_pathvar(char *envp[])
{
	int		i;
	char	path[6];
	char	**path_arr;

	ft_strlcpy(path, "PATH=", 6);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], path, 5) == 0)
			break ;
		i++;
	}
	path_arr = ft_split(envp[i], ':');
	// Protection?
	ft_memmove(path_arr[0], path_arr[0] + 5, ft_strlen(path_arr[0]) - 4);
	return (path_arr);
}

// Calculates the amount of memory necessary for the longest combination of
// a $PATH value and the used shell command, by adding the lengths together.
static int	find_pathlen(char **argv, char **pathdir)
{
	int	arglen;
	int	pathlen;
	int	i;

	i = 0;
	arglen = ft_strlen(argv[2]);
	if (arglen < ft_strlen(argv[3]))
		arglen = ft_strlen(argv[3]);
	pathlen = ft_strlen(pathdir[i]);
	i++;
	while (pathdir[i] != NULL)
	{
		if (pathlen < ft_strlen(pathdir[i]))
			pathlen = ft_strlen(pathdir[i]);
		i++;
	}
	return (arglen + pathlen + 2);
}

// ft_split for any additional arguments being passed to execve
static char	**find_execargs(char *argv)
{
	char	**arg_arr;

	arg_arr = ft_split(argv, ' ');
	// protec?
	return (arg_arr);
}

// Set up the struct that contains all the data we need for the following
// functions.
t_data	*build_struct(char **argv, char **envp)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	// protection
	new->argv = argv;
	new->envp = envp;
	new->pathdir = find_pathvar(envp);
	new->execargs1 = find_execargs(argv[2]);
	new->execargs2 = find_execargs(argv[3]);
	// protection
	new->maxpathlen = find_pathlen(argv, new->pathdir);
	return (new);
}
