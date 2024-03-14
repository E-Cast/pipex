/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:04:52 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/14 17:18:46 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_outfile(char *outfile, int flag, int *last_cmd)
{
	int	output_file;

	if (access(outfile, W_OK) == 0 || errno == ENOENT)
		output_file = open(outfile, O_CREAT | O_WRONLY | flag, 0664);
	else if (errno == EACCES)
	{
		output_file = open("/dev/null", O_CREAT | O_WRONLY | flag, 0664);
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(outfile, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		*last_cmd -= 1;
	}
	else
		return (-1);
	if (output_file == -1)
		return (-1);
	return (output_file);
}

int	open_output(int argc, char **argv, int *last_cmd)
{
	int	output_fd;

	*last_cmd = argc - 2;
	if (my_strcmp(argv[1], "here_doc") == 0)
		output_fd = open_outfile(argv[argc - 1], O_APPEND, last_cmd);
	else
		output_fd = open_outfile(argv[argc - 1], O_TRUNC, last_cmd);
	if (output_fd == -1)
		return (-1);
	return (output_fd);
}
