/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:42:17 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/01 15:21:16 by acourtar         ###   ########.fr       */
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

// Finds the $PATH variable in the environment, 
// then puts all the possible PATHs in a list using ft_split
static char	**find_pathvar(char *envp[], int *pathavail)
{
	int		i;
	char	path[6];
	char	**path_arr;

	ft_strlcpy(path, "PATH=", 6);
	i = 0;
	ft_printf("%s\n", envp[i]);
	while (1)
	{
		ft_printf("%s\n", envp[i]);
		if (envp[i] != NULL && ft_strncmp(envp[i], path, 5) == 0)
			break ;
		if (envp[i] == NULL)
		{
			*pathavail = 0;
			return (NULL);
		}
		i++;
	}
	path_arr = ft_split(envp[i], ':');
	if (path_arr == NULL)
		return (NULL);
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
	arglen = ft_strlen("touch");
	if (arglen < ft_strlen(argv[2]))
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
	if (arg_arr == NULL)
		return (NULL);
	return (arg_arr);
}

// Set up the struct that contains all the data we need for the following
// functions.
t_data	*build_struct(char **argv, char **envp)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (new == NULL)
		exit_func();
	new->argv = argv;
	new->envp = envp;
	new->pathav = 1;
	new->pathdir = find_pathvar(envp, &(new->pathav));
	if (new->pathdir == NULL && new->pathav == 1)
		exit_func();
	new->execargs1 = find_execargs(argv[2]);
	if (new->execargs1 == NULL)
		exit_func();
	new->execargs2 = find_execargs(argv[3]);
	if (new->execargs2 == NULL)
		exit_func();
	new->maxpathlen = find_pathlen(argv, new->pathdir);
	new->err[0] = 0;
	new->err[1] = 0;
	return (new);
}
