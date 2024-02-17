/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_old.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:17:32 by ecastong          #+#    #+#             */
/*   Updated: 2024/02/16 21:33:02 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_OLD_H
# define PIPEX_OLD_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_fd
{
	int	infile;
	int	outfile;
	int	pipe1[2];
	int	pipe2[2];
	int	input;
	int	output;

}	t_fd;

t_fd	open_files(t_fd fd, int argc, char **argv);
t_fd	open_pipes(t_fd fd);
t_fd	get_used(t_fd fd, int counter, int argc);
void	close_unused(t_fd fd, int used1, int used2);

char	**split_string(char	*string);

void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
char	*concat(const char *src1, const char *src2);
void	terminate(char **array, int status);

// t_fd	fd_open_all(t_fd fd, int argc, char **argv);
// t_fd	fd_get_used(t_fd fd, int counter, int argc);
// void	fd_close_unused(t_fd fd, int input, int output);

#endif