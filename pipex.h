/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:01:35 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/25 13:30:22 by acourtar         ###   ########.fr       */
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

#endif