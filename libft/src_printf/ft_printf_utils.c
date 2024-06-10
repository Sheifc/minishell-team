/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:36:34 by sheferna          #+#    #+#             */
/*   Updated: 2024/02/28 15:15:01 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_pf(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_pf(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (*str)
		i += write(1, str++, 1);
	return (i);
}

int	ft_putptr_pf(unsigned long ptr)
{
	int		i;

	i = 0;
	i += ft_putstr_pf("0x");
	if (ptr == 0)
		i += ft_putchar_pf('0');
	else
		i += ft_putnbrbase_ptr_pf(ptr, 16, "0123456789abcdef");
	return (i);
}

int	ft_putnbrbase_pf(long n, int base, const char *base_digits)
{
	int	i;

	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_putnbrbase_pf(-n, base, base_digits) + 1);
	}
	if (n < base)
		return (ft_putchar_pf(base_digits[n]));
	else
	{
		i = ft_putnbrbase_pf(n / base, base, base_digits);
		return (i + ft_putnbrbase_pf(n % base, base, base_digits));
	}
}

int	ft_putnbrbase_ptr_pf(unsigned long n, int base, const char *base_digits)
{
	int	i;

	if (n < (unsigned long) base)
		return (ft_putchar_pf(base_digits[n]));
	else
	{
		i = ft_putnbrbase_ptr_pf(n / base, base, base_digits);
		return (i + ft_putnbrbase_ptr_pf(n % base, base, base_digits));
	}
}
