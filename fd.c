/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 07:38:41 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/15 08:50:10 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fd_close_unused(t_fd fd)
{
	if (fd.input != fd.infile)
		close(fd.infile);
	if (fd.input != fd.pipe1[0])
		close(fd.pipe1[0]);
	if (fd.input != fd.pipe2[0])
		close(fd.pipe2[0]);
	if (fd.output != fd.outfile)
		close(fd.outfile);
	if (fd.output != fd.pipe1[1])
		close(fd.pipe1[1]);
	if (fd.output != fd.pipe2[1])
		close(fd.pipe2[1]);
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
