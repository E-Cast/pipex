/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:16:29 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/16 05:05:35 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*strldup(const char *src, size_t len, char **array)
{
	char	*dest;
	size_t	i;

	if (!src)
		return (NULL);
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		terminate(array, EXIT_FAILURE);
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
		terminate(array, EXIT_FAILURE);
	j = 0;
	while (string[0])
	{
		i = 0;
		while (string[i] != ' ' && string[i] != '\0')
			i++;
		array[j] = strldup(string, i, array);
		if (string[i] == '\0')
			return (array);
		string = &string[i + 1];
		j++;
	}
	return (array);
}
