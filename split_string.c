/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:16:29 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/13 01:07:23 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*strldup(const char *src, size_t len)
{
	char	*dest;
	size_t	i;

	if (!src)
		return (NULL);
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		exit(EXIT_FAILURE); // will cause leaks
	i = 0;
	while (i < len && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**split_string(char	*string)
{
	int		i;
	int		j;
	char	**array;

	i = 0;
	j = 2;
	while (string[i])
		if (string[i++] == ' ')
			j++;
	array = ft_calloc(j, sizeof(char *));
	if (!array)
		exit(EXIT_FAILURE); // will cause leaks
	j = 0;
	while (string[0])
	{
		i = 0;
		while (string[i] != ' ' && string[i] != '\0')
			i++;
		array[j] = strldup(string, i);
		if (string[i] == '\0')
			return (array);
		string = &string[i + 1];
		j++;
	}
	return (array);
}
