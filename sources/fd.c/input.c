/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:29:18 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/14 12:21:26 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_heredoc(char *delimiter, int *first_cmd)
{
	int		heredoc_pipe[2];
	char	*input;

	if (pipe(heredoc_pipe) == -1)
		return (-1);
	ft_putstr_fd("> ", STDOUT_FILENO);
	input = get_next_line(STDIN_FILENO);
	while (input != NULL)
	{
		if (ft_strncmp(input, delimiter, ft_strlen(input) - 1) == 0)
			break ;
		ft_putstr_fd(input, heredoc_pipe[1]);
		my_safefree(input);
		ft_putstr_fd("> ", STDOUT_FILENO);
		input = get_next_line(STDIN_FILENO);
	}
	my_safefree(input);
	close(heredoc_pipe[1]);
	*first_cmd += 1;
	return (heredoc_pipe[0]);
}

int	open_infile(char *infile, int *first_cmd)
{
	int	input_file;

	if (access(infile, R_OK) == 0)
		input_file = open(infile, O_RDONLY);
	else if (errno == ENOENT || errno == EACCES)
	{
		input_file = open("/dev/null", O_RDONLY);
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(infile, STDERR_FILENO);
		if (errno == ENOENT)
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		if (errno == EACCES)
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
		*first_cmd += 1;
	}
	else
		return (-1);
	if (input_file == -1)
		return (-1);
	return (input_file);
}

int	open_input(char **argv, int *first_cmd)
{
	int	input_fd;

	*first_cmd = 2;
	if (my_strcmp(argv[1], "here_doc") == 0)
		input_fd = open_heredoc(argv[2], first_cmd);
	else
		input_fd = open_infile(argv[1], first_cmd);
	if (input_fd == -1)
		exit(EXIT_FAILURE);
	return (input_fd);
}
