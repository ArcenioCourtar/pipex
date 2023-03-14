/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:12:43 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/19 09:26:32 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// If character 'c' is a lowercase letter, convert to uppercase
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
