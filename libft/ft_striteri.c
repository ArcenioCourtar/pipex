/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:41:19 by acourtar          #+#    #+#             */
/*   Updated: 2022/10/26 14:33:55 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Perform function 'f' on each character of string 's'.
// First arg of 'f' is the index of the character to be modified.
// Second arg is the address of the character to be modified by 'f'.
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
