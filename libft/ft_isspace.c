/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:56:24 by acourtar          #+#    #+#             */
/*   Updated: 2023/02/07 16:00:43 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns 1 if the character is a space or something equivalent
int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\f')
		return (1);
	if (c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}
