/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:14:06 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/08 15:55:49 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <stdlib.h>	// exit()
#include <stdio.h>	// perror()
#include <errno.h>	// errno

// Print error, and exit program after.
void	err_exit(void)
{
	perror("");
	exit(EXIT_FAILURE);
}

// Count # of arguments, if it's not the correct amount, print help message.
void	check_args(int argc)
{
	if (argc != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		exit(EXIT_SUCCESS);
	}
}

/*
Program overview:
Count the # of arguments, if its correct, continue.
Assign values and allocate memory to struct members based on arguments given.
Check if the files in the arguments exist, and if we have access permissions.
Set up fds based on results of previous function.
fork() this process and write/read through pipe.
*/
int	main(int argc, char **argv, char **envp)
{
	int		origfd[2];
	t_data	dat;	

	check_args(argc);
	build_struct(argv, envp, &dat);
	access_open(&dat);
	fd_setup(origfd, &dat);
	cmd_exec(origfd, &dat);
	exit(0);
}
