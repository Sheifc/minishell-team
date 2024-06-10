/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:00:36 by sheferna          #+#    #+#             */
/*   Updated: 2023/10/14 13:31:21 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*p;

	len = ft_strlen(s1) + 1;
	p = (char *)malloc(sizeof(char) * len);
	i = -1;
	if (!p)
		return (NULL);
	while (s1[++i])
		p[i] = s1[i];
	p[i] = '\0';
	return (p);
}
