/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:43:13 by sheferna          #+#    #+#             */
/*   Updated: 2023/09/25 12:30:58 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	result;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst < dstsize)
		result = (len_dst + len_src);
	else
		result = (len_src + dstsize);
	while (*src && (len_dst + 1) < dstsize)
	{
		dst[len_dst] = *src;
		len_dst++;
		src++;
	}
	if (len_dst < dstsize)
		dst[len_dst] = '\0';
	return (result);
}
