/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:07:26 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/13 02:48:12 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
		ptr[i++] = 0;
	return ((void *)ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*concat(const char *src1, const char *src2)
{
	size_t	dest_len;
	char	*dest;
	size_t	i;
	size_t	j;

	if (!src1 || !src2)
		return (NULL);
	dest_len = ft_strlen(src1) + ft_strlen(src2);
	dest = ft_calloc(dest_len + 1, sizeof(char));
	i = 0;
	j = 0;
	while (src1[i])
	{
		dest[i] = src1[i];
		i++;
	}
	while (src2[j])
		dest[i++] = src2[j++];
	dest[i] = '\0';
	return (dest);
}

void	terminate(char **array, int status)
{
	int	i;

	while (array && array[i])
		free(array[i++]);
	if (array)
		free(array);
	exit(status);
}
