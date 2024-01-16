/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 07:38:41 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/16 04:43:56 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_fd	fd_open_all(t_fd fd, int argc, char **argv)
{
	fd.infile = open(argv[1], O_RDONLY | __O_CLOEXEC);
	if (fd.infile == -1)
		exit(EXIT_FAILURE);
	fd.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY | __O_CLOEXEC, 0644);
	if (fd.outfile == -1)
	{
		fd_close_unused(fd, -1, -1);
		exit(EXIT_FAILURE);
	}
	if (pipe(fd.pipe1) == -1)
	{
		fd_close_unused(fd, -1, -1);
		exit(EXIT_FAILURE);
	}
	if (pipe(fd.pipe2) == -1)
	{
		fd_close_unused(fd, -1, -1);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

t_fd	fd_get_used(t_fd fd, int counter, int argc)
{
	if (counter == 2)
		fd.input = fd.infile;
	else if (counter % 2)
		fd.input = fd.pipe1[0];
	else
		fd.input = fd.pipe2[0];
	if (counter + 1 == argc -1)
		fd.output = fd.outfile;
	else if (counter % 2)
		fd.output = fd.pipe2[1];
	else
		fd.output = fd.pipe1[1];
	return (fd);
}

void	fd_close_unused(t_fd fd, int input, int output)
{
	if (input != fd.infile)
		close(fd.infile);
	if (input != fd.pipe1[0])
		close(fd.pipe1[0]);
	if (input != fd.pipe2[0])
		close(fd.pipe2[0]);
	if (output != fd.outfile)
		close(fd.outfile);
	if (output != fd.pipe1[1])
		close(fd.pipe1[1]);
	if (output != fd.pipe2[1])
		close(fd.pipe2[1]);
}
