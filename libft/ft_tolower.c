/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:04:51 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/19 09:26:14 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// If character 'c' is an uppercase letter, convert to lowercase
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
