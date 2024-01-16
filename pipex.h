/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:17:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/16 04:33:36 by ecastong         ###   ########.fr       */
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

t_fd	fd_open_all(t_fd fd, int argc, char **argv);
t_fd	fd_get_used(t_fd fd, int counter, int argc);
void	fd_close_unused(t_fd fd, int input, int output);

#endif