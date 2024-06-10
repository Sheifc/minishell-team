/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:01:43 by sheferna          #+#    #+#             */
/*   Updated: 2024/02/28 15:15:08 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format(char format, va_list ap)
{
	int			i;

	i = 0;
	if (format == 'c')
		i += ft_putchar_pf(va_arg(ap, int));
	else if (format == 's')
		i += ft_putstr_pf(va_arg(ap, char *));
	else if (format == 'p')
		i += ft_putptr_pf(va_arg(ap, unsigned long));
	else if (format == 'd' || format == 'i')
		i += ft_putnbrbase_pf((long)va_arg(ap, int), 10, \
		"0123456789");
	else if (format == 'u')
		i += ft_putnbrbase_pf((long)va_arg(ap, unsigned int), 10, \
		"0123456789");
	else if (format == 'x')
		i += ft_putnbrbase_pf((long)va_arg(ap, unsigned int), 16, \
		"0123456789abcdef");
	else if (format == 'X')
		i += ft_putnbrbase_pf((long)va_arg(ap, unsigned int), 16, \
		"0123456789ABCDEF");
	else
		i += write(1, &format, 1);
	return (i);
}

int	ft_printf(char const *format, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, format);
	if (write(1, "", 0) == -1)
		return (-1);
	i = 0;
	while (*format)
	{
		if (*format == '%')
			i += print_format(*(++format), ap);
		else
			i += write(1, format, 1);
		++format;
	}
	va_end(ap);
	return (i);
}
