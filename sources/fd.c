/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:49:11 by ecast             #+#    #+#             */
/*   Updated: 2024/02/22 02:59:22 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_heredoc(t_pipex *pipex, char *limiter)
{
	int		hd_pipe[2];
	char	*input;

	if (pipe(hd_pipe) == -1)
		return ;//terminate
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	input = get_next_line(STDIN_FILENO);
	while (input != NULL)
	{
		if (ft_strncmp(input, limiter, ft_strlen(input) - 1) == 0)
			break ;
		ft_putstr_fd(input, hd_pipe[1]);
		my_safefree(input);
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		input = get_next_line(STDIN_FILENO);
	}
	my_safefree(input);
	close(hd_pipe[1]);
	pipex->input_file = hd_pipe[0];
}

void	open_infile(t_pipex *pipex, char *infile)
{
	if (access(infile, R_OK) == 0)
		pipex->input_file = open(infile, O_RDONLY);
	else if (errno == ENOENT || errno == EACCES)
		pipex->input_file = open("/dev/null", O_RDONLY);
	else
		return ;//terminate
	if (pipex->output_file == -1)
		return ;//terminate
}

void	open_outfile(t_pipex *pipex, char *outfile, int flag)
{
	if (access(outfile, W_OK) == 0 || errno == ENOENT)
		pipex->output_file = open(outfile, O_CREAT | O_WRONLY | flag, 0664);
	else if (errno == EACCES)
		pipex->output_file = open("/dev/null", O_CREAT | O_WRONLY | flag, 0664);
	else
		return ;//terminate
	if (pipex->output_file == -1)
		return ;//terminate
}
