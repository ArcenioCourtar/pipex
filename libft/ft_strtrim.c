/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:42:25 by acourtar          #+#    #+#             */
/*   Updated: 2022/11/22 15:13:05 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static int	set_cmp(char const *set, char c);
static int	ltr_check(char const *s1, char const *set);
static int	rtl_check(char const *s1, char const *set);
static void	write_str(char const *s1, char *str, int start, int end);

// Trims the beginning and end of string 's1' of characters in 'set'.
// Returns the trimmed string in newly allocated memory.
char	*ft_strtrim(char const *s1, char const *set)
{
	int		end;
	int		start;
	char	*str;

	start = ltr_check(s1, set);
	end = rtl_check(s1, set);
	str = malloc(end - start + 1);
	if (str == NULL)
		return (NULL);
	write_str(s1, str, start, end);
	return (str);
}

// Compares current character to every character in the given set.
static int	set_cmp(char const *set, char c)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

// Checks string from left to right for characters in the set.
static int	ltr_check(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (set_cmp(set, s1[i]) == 1)
			i++;
		else
			return (i);
	}
	return (0);
}

// Checks string from right to left for characters in the set.
static int	rtl_check(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		if (set_cmp(set, s1[i]) == 1)
			i--;
		else
			return (i + 1);
	}
	return (i + 1);
}

// Writes the new trimmed string into malloced memory.
static void	write_str(char const *s1, char *str, int start, int end)
{
	int	i;

	i = 0;
	while (start < end)
	{
		str[i] = s1[start];
		start++;
		i++;
	}
	str[i] = '\0';
}
