/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:14:14 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/28 16:47:51 by acourtar         ###   ########.fr       */
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
	int		err[2];
	int		maxpathlen;
}	t_data;

void	exit_func(void);
t_data	*build_struct(char **argv, char **envp);
void	cmd_exec(int origfd[2], int pipefd[2], t_data *data);

#endif