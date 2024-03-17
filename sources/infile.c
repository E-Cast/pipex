/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:27:40 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/17 15:41:09 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_heredoc(char *delimiter)
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
	return (heredoc_pipe[0]);
}

int	open_infile(char **argv)
{
	int		input_file;
	char	*infile;

	if (my_strcmp(argv[1], "here_doc") == 0)
		return (open_heredoc(argv[2]));
	else
		infile = argv[1];
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
	}
	else
		return (-1);
	if (input_file == -1)
		return (-1);
	return (input_file);
}

int	main(int argc, char **argv)
{
	int	fd;

	fd = open_infile(argv);
	if (fd == -1)
		printf("error\n");
	else
		printf("success\n");
	close(fd);
	return (0);
	(void) argc;
}
