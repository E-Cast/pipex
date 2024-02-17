/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:38:57 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/19 08:56:15 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_fd	open_pipes(t_fd fd)
{
	if (pipe(fd.pipe1) == -1)
	{
		close_unused(fd, -1, -1);
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd.pipe2) == -1)
	{
		close_unused(fd, -1, -1);
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

t_fd	open_files(t_fd fd, int argc, char **argv)
{
	fd.infile = open(argv[1], O_RDONLY);
	if (fd.infile == -1 && (errno == ENOENT || errno == EACCES))
	{
		perror(argv[1]);
		fd.infile = open("/dev/null", O_RDONLY);
	}
	if (fd.infile == -1)
	{
		perror(argv[argc - 1]);
		exit(EXIT_FAILURE);
	}
	fd.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (fd.outfile == -1 && errno == EACCES)
	{
		perror(argv[argc - 1]);
		fd.outfile = open("/dev/null", O_WRONLY);
	}
	if (fd.outfile == -1)
	{
		perror(argv[argc - 1]);
		close(fd.infile);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

t_fd	get_used(t_fd fd, int counter, int argc)
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

void	close_unused(t_fd fd, int used1, int used2)
{
	if (fd.infile != used1 && fd.infile == used2)
		close(fd.infile);
	if (fd.outfile != used1 && fd.outfile == used2)
		close(fd.outfile);
	if (fd.pipe1[0] != used1 && fd.pipe1[0] == used2)
		close(fd.pipe1[0]);
	if (fd.pipe1[1] != used1 && fd.pipe1[1] == used2)
		close(fd.pipe1[1]);
	if (fd.pipe2[0] != used1 && fd.pipe2[0] == used2)
		close(fd.pipe2[0]);
	if (fd.pipe2[1] != used1 && fd.pipe2[1] == used2)
		close(fd.pipe2[1]);
	if (fd.input != used1 && fd.input == used2)
		close(fd.input);
	if (fd.output != used1 && fd.output == used2)
		close(fd.output);
}