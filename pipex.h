/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:01:35 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/25 19:40:24 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_data
{
	char	**argv;
	char	**pathdir;
	char	**execargs1;
	char	**execargs2;
	char	**envp;
	int		maxpathlen;
}	t_data;

void	parent_func(int pipefd[2], int f2, int child, t_data *data);
void	child_func(int pipefd[2], int f1, t_data *data);
int		openfd(int origfd[2], int pipefd[2], t_data *data);
void	create_path(char *goal, char *dir, char *file);
t_data	*build_struct(char **argv, char **envp);

#endif