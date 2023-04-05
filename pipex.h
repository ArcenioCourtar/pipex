/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:14:14 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/05 13:27:31 by acourtar         ###   ########.fr       */
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
	int		pathav;
	int		maxpathlen;
}	t_data;

// allocate memory and fill struct with the relevant data
t_data	*build_struct(char **argv, char **envp);

// execute commands
void	cmd_exec(int origfd[2], t_data *data);
// check existence of specified file, and permissions
void	access_open(t_data *data);
// set up fd's according to the results found in access_open()
void	fd_setup(int origfd[2], t_data *data);
// Creates the final exec path by going through all the $PATH directories
// and concatenating the user's input behind it.
// Behaviour changes if there is no PATH or user inputs an absolute path.
// calls execve() once path has been created.
void	build_path(char *goaldir, char **execargs, t_data *dat);
// Print error, then exit() program.
void	err_exit(void);

#endif