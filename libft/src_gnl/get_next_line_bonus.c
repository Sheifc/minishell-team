/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:38:03 by sheferna          #+#    #+#             */
/*   Updated: 2024/04/06 13:27:40 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_read(int fd, char *estatic)
{
	int		nbytes;
	char	*buffer;

	nbytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&estatic));
	buffer[0] = '\0';
	while (nbytes > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		nbytes = read (fd, buffer, BUFFER_SIZE);
		if (nbytes > 0)
		{
			buffer[nbytes] = '\0';
			estatic = ft_strjoin_gnl(estatic, buffer);
		}
	}
	free(buffer);
	if (nbytes == -1)
		return (ft_free(&estatic));
	return (estatic);
}

char	*ft_get_line(char *estatic)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr_gnl(estatic, '\n');
	len = (ptr - estatic) + 1;
	line = ft_substr_gnl(estatic, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_new_estatic(char *estatic)
{
	char	*new_estatic;
	char	*ptr;
	int		len;

	ptr = ft_strchr_gnl(estatic, '\n');
	if (!ptr)
	{
		new_estatic = NULL;
		return (ft_free(&estatic));
	}
	else
		len = (ptr - estatic) + 1;
	if (!estatic[len])
		return (ft_free(&estatic));
	new_estatic = ft_substr_gnl(estatic, len, ft_strlen(estatic) - len);
	ft_free(&estatic);
	if (!new_estatic)
		return (NULL);
	return (new_estatic);
}

char	*get_next_line(int fd)
{
	static char	*estatic[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((estatic[fd] && !ft_strchr_gnl(estatic[fd], '\n')) || !estatic[fd])
		estatic[fd] = ft_read(fd, estatic[fd]);
	if (!estatic[fd])
		return (NULL);
	line = ft_get_line(estatic[fd]);
	if (!line)
		return (ft_free(&estatic[fd]));
	estatic[fd] = ft_new_estatic(estatic[fd]);
	return (line);
}
