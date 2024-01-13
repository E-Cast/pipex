/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:17:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/13 01:13:23 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_args
{
	char	*infile;
	char	*outfile;
	char	***commands;

}	t_args;

char	**split_string(char	*string);

void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
char	*concat(const char *src1, const char *src2);

#endif