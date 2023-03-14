/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 09:34:26 by acourtar          #+#    #+#             */
/*   Updated: 2022/11/16 18:42:35 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>

static int	select_conversion(va_list args, char c);
static int	numlen_calc(long i);
static int	num_conversion(uintptr_t i, char c, int base, int called);

// Mirror functionality from printf.
// Minus the hard stuff. xd
int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, str);
	while (str[0] != '\0')
	{
		if (str[0] == '%' && str[1] != '\0')
		{
			if (str[1] == '%')
				ft_putchar_fd('%', 1);
			else
				len += select_conversion(args, str[1]) - 1;
			str++;
		}
		else
			ft_putchar_fd(*str, 1);
		len++;
		str++;
	}
	va_end(args);
	return (len);
}

// Call this function after a '%' is encountered in 'str'
// Act accordingly based on what's encountered after the '%'
static int	select_conversion(va_list args, char c)
{
	char	*str;

	if (c == 's')
	{
		str = va_arg(args, char *);
		if (str == NULL)
		{
			ft_putstr_fd("(null)", 1);
			return (6);
		}
		ft_putstr_fd(str, 1);
		return ((int)ft_strlen(str));
	}
	else if (c == 'i' || c == 'd')
		return (numlen_calc(va_arg(args, int)));
	else if (c == 'u')
		return (num_conversion(va_arg(args, unsigned int), c, 10, 0));
	else if (c == 'x' || c == 'X')
		return (num_conversion(va_arg(args, unsigned int), c, 16, 0));
	else if (c == 'p')
		return (num_conversion(va_arg(args, uintptr_t), c, 16, 0));
	else if (c == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	return (1);
}

// Calculate and return the length of 'i' given as argument,
// Print the corresponding characters as well.
static int	numlen_calc(long i)
{
	int	numlen;

	ft_putnbr_fd(i, 1);
	if (i == 0)
		return (1);
	if (i < 0)
	{
		numlen = 2;
		i *= -1;
	}
	else
		numlen = 1;
	while (i > 9)
	{
		i = i / 10;
		numlen++;
	}
	return (numlen);
}

// Converts the number 'i' into it's 'base' equivalent.
// Handles all unsigned numbers, including pointers.
static int	num_conversion(uintptr_t i, char c, int base, int called)
{
	char	*hex_chars;
	int		len;

	len = 0;
	if (called == 0 && c == 'p')
	{
		ft_putstr_fd("0x", 1);
		len += 2;
	}
	if (called == 0 && i == 0)
	{
		ft_putchar_fd('0', 1);
		return (len + 1);
	}
	if (c == 'X')
		hex_chars = "0123456789ABCDEF";
	else
		hex_chars = "0123456789abcdef";
	if (i != 0)
	{
		len += num_conversion((i / base), c, base, 1);
		len++;
		ft_putchar_fd(hex_chars[i % base], 1);
	}
	return (len);
}
