/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 07:54:10 by sheferna          #+#    #+#             */
/*   Updated: 2024/07/07 14:14:07 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_wordcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')))
			count++;
		i++;
	}
	return (count);
}

static	char	**write_result(char const *s, char c, char	**matrix)
{
	size_t	i;
	size_t	start;
	size_t	word;

	i = 0;
	start = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			matrix[word] = ft_substr(s, start, i - start + 1);
			if (!matrix[word])
			{
				ft_free_matrix(matrix);
				return (0);
			}
			word++;
		}
		if (s[i] == c && (s[i + 1] != c || s[i + 1] != '\0'))
			start = i + 1;
		i++;
	}
	matrix[word] = 0;
	return (matrix);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;

	if (!s)
		return (0);
	matrix = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!matrix)
		return (0);
	matrix = write_result(s, c, matrix);
	return (matrix);
}
