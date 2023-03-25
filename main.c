/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:01:20 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/25 13:48:04 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>		// pipe(), close(), read(), execve(), dup2()
#include <fcntl.h>		// open()
#include <stdlib.h>		// exit()
#include <sys/wait.h>	// wait()
#include <stdio.h>		// printf(), perror(), environ

void	check_args(int argc)
{
	if (argc != 5)
	{
		write(STDOUT_FILENO, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38);
		exit(EXIT_SUCCESS);
	}
}

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

	i = 0;
	len = ft_strlen(dir);
	ft_memcpy(goal, dir, len);
	i = len;
	goal[i] = '/';
	len = ft_strlen(file);
	ft_memcpy(goal + i + 1, file, len);
	goal[i + len + 1] = '\0';
}

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

char	**find_pathvar(char *envp[])
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

int	find_pathlen(char **argv, char **pathdir)
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

char	**find_execargs(char *argv)
{
	char	**arg_arr;

	arg_arr = ft_split(argv, ' ');
	return (arg_arr);
}

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

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	int		origfd[2];
	int		pidstat;
	t_data	*data;

	check_args(argc);
	data = build_struct(argv, envp);
	// protection
	openfd(origfd, pipefd, argv);
	pidstat = fork();
	if (pidstat < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	else if (pidstat == 0)
		child_func(pipefd, origfd[0], data);
	else
		parent_func(pipefd, origfd[1], pidstat, data);
	return (0);
}
