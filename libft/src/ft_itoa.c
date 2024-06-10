/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:26:20 by sheferna          #+#    #+#             */
/*   Updated: 2023/10/13 17:44:03 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(long n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		len;
	long	nbr;

	nbr = (long)n;
	len = ft_length(nbr);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	p[len] = '\0';
	if (nbr == 0)
		p[0] = '0';
	if (nbr < 0)
	{
		p[0] = '-';
		nbr = -nbr;
	}
	while (nbr > 9)
	{
		p[--len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (nbr > 0)
		p[--len] = nbr + '0';
	return (p);
}
