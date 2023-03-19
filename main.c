/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:01:20 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/14 18:13:42 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>		// pipe(), close(), read(), execve()
#include <fcntl.h>		// open()
#include <stdlib.h>		// exit()
#include <sys/wait.h>	// wait()
#include <stdio.h>		// printf()

int main(int argc, char *argv[])
{
	int 	f1, f2;
	int 	pipefd[2];
	char	buf[1000];
	pid_t 	forkpid;

	if (argc != 5)
	{
		ft_printf("too few args\n");
		exit(EXIT_SUCCESS);
	}
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_WRONLY);
	if (f1 < 0 || f2 < 0)
	{
		perror("");
		exit(EXIT_SUCCESS);
	}
	ft_bzero(buf, 1000);
	pipe(pipefd);
	forkpid = fork();
	if (forkpid < 0)
	{
		perror("fork error");
	}
	else if (forkpid == 0)	// child
	{
		close(pipefd[0]);
		read(f1, buf, 1000);
		write(pipefd[1], buf, 1000);
		close(pipefd[1]);
	}
	else	// parent
	{
		close(pipefd[1]);
		wait(&forkpid);
		read(pipefd[0], buf, 1000);
		write(f2, buf, ft_strlen(buf));
		close(pipefd[0]);
	}
}
