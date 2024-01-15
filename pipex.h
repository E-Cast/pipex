/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:17:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/15 07:04:40 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_fd
{
	int	infile;
	int	outfile;
	int	pipe1[2];
	int	pipe2[2];
	int	input;
	int	output;

}	t_fd;

char	**split_string(char	*string);

void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
char	*concat(const char *src1, const char *src2);
void	terminate(char **array, int status);

#endif