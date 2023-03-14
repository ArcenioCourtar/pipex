/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:51:07 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/26 14:25:49 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// Frees the content of a single node (with del()) as well as the
// node itself. del() should NOT free lst->next.
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del((*lst).content);
	free(lst);
}
