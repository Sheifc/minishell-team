/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:38:03 by sheferna          #+#    #+#             */
/*   Updated: 2024/07/06 11:36:59 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

    if (!matrix)
        return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
        matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}
