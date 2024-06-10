/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheferna <sheferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:20:30 by sheferna          #+#    #+#             */
/*   Updated: 2024/04/03 09:53:51 by sheferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	is_delim(char c, const char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim++)
			return (1);
	}
	return (0);
}

static char	*skip_delim(char *str, const char *delim)
{
	while (*str && is_delim(*str, delim))
		str++;
	return (str);
}

static char	*find_token_end(char *str, const char *delim)
{
	char	*token_end;

	token_end = str;
	while (*token_end && !is_delim(*token_end, delim))
		token_end++;
	return (token_end);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next_token;
	char		*token_end;

	if (str)
		next_token = str;
	else if (!next_token || !*next_token)
		return (NULL);
	str = skip_delim(next_token, delim);
	if (!*str)
		return (next_token = str, NULL);
	token_end = find_token_end(str, delim);
	if (*token_end)
	{
		*token_end = '\0';
		next_token = token_end + 1;
	}
	else
		next_token = token_end;
	return (str);
}
