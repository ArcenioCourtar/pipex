/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:38:37 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/08 15:41:45 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>		// execve()
#include <errno.h>		// errno

// creates full pathnames to the file we're looking for by 
// copying the contents of dir and file into the previously allocated
// memory of goal.
// If the user specified a full path, just check that once instead.
// If the user specifies an empty string or a string  with exclusively
// spaces, don't attempt to append *file to *dir
static void	create_path(char *goal, char *dir, char *file, int *pathav)
{
	int	i;
	int	len;

	if (file != NULL && (dir == NULL || ft_strchr(file, '/') != NULL))
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
	goal[i + 1] = '\0';
	len = ft_strlen(file);
	ft_memcpy(goal + i + 1, file, len + 1);
}

// Check if the $PATH variable is available. If it is, go through all possible
// paths to see if execve() gets a "hit".
// If the $PATH is not available (or the user hands an absolute path as arg), 
// only do a single check.
void	build_path(char *goaldir, char **execargs, t_data *dat)
{
	int	i;

	i = 0;
	while (dat->pathav == 1 && dat->pathdir[i] != NULL && execargs[0] != NULL)
	{
		create_path(goaldir, dat->pathdir[i], execargs[0], &(dat->pathav));
		execve(goaldir, execargs, dat->envp);
		i++;
	}
	if (dat->pathav == 0 && execargs[0] != NULL)
	{
		create_path(goaldir, NULL, execargs[0], &(dat->pathav));
		execve(goaldir, execargs, dat->envp);
	}
	if (dat->pathdir == NULL)
		dat->pathav = -1;
}
