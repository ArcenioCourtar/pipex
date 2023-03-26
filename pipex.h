/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:14:14 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/26 20:08:59 by acourtar         ###   ########.fr       */
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

#endif