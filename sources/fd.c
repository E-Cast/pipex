/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:49:11 by ecast             #+#    #+#             */
/*   Updated: 2024/03/07 17:06:55 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Prints the required amount of "pipe " to 
	stdout followed by "pipe heredoc> ".*/
void	put_heredoc(t_pipex *pipex)
{
	int	count;

	count = (pipex->last_cmd - (pipex->first_cmd - 1) - 2);
	while (count--)
		ft_putstr_fd("pipe ", STDOUT_FILENO);
	ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
}

/*Emulates zsh's here document: It takes strings as input from 
	the terminal until it receives the delimiter and puts those 
	strings in a pipe. It then sets that pipe as input file in pipex.*/
void	open_heredoc(t_pipex *pipex, char *delimiter)
{
	int		hd_pipe[2];
	char	*input;

	if (pipe(hd_pipe) == -1)
		terminate(pipex, EXIT_FAILURE, errno, "pipex: pipe");
	put_heredoc(pipex);
	input = get_next_line(STDIN_FILENO);
	while (input != NULL)
	{
		if (ft_strncmp(input, delimiter, ft_strlen(input) - 1) == 0)
			break ;
		ft_putstr_fd(input, hd_pipe[1]);
		my_safefree(input);
		put_heredoc(pipex);
		input = get_next_line(STDIN_FILENO);
	}
	my_safefree(input);
	close(hd_pipe[1]);
	pipex->input_file = hd_pipe[0];
}

/*Opens and sets the input file while handling any error that might come up.*/
void	open_infile(t_pipex *pipex, char *infile)
{
	if (access(infile, R_OK) == 0)
		pipex->input_file = open(infile, O_RDONLY);
	else if (errno == ENOENT || errno == EACCES)
	{
		pipex->input_file = open("/dev/null", O_RDONLY);
		ft_putstr_fd("pipex: permission denied: ", STDERR_FILENO);
		ft_putendl_fd(infile, STDERR_FILENO);
		pipex->first_cmd += 1;
	}
	else
		terminate(pipex, EXIT_FAILURE, errno, "pipex: open");
	if (pipex->input_file == -1)
		terminate(pipex, EXIT_FAILURE, errno, "pipex: open");
}

/*Opens and sets the output file while handling any error that might come up.*/
void	open_outfile(t_pipex *pipex, char *outfile, int flag)
{
	if (access(outfile, W_OK) == 0 || errno == ENOENT)
		pipex->output_file = open(outfile, O_CREAT | O_WRONLY | flag, 0664);
	else if (errno == EACCES)
	{
		pipex->output_file = open("/dev/null", O_CREAT | O_WRONLY | flag, 0664);
		ft_putstr_fd("pipex: permission denied: ", STDERR_FILENO);
		ft_putendl_fd(outfile, STDERR_FILENO);
		pipex->last_cmd -= 1;
	}
	else
		terminate(pipex, EXIT_FAILURE, errno, "pipex: open");
	if (pipex->output_file == -1)
		terminate(pipex, EXIT_FAILURE, errno, "pipex: open");
}

/*Calls all the relevant open_ functions and opens the pipes needed by pipex.*/
void	open_fds(t_pipex *pipex, int argc, char **argv)
{
	pipex->last_cmd = argc - 2;
	if (my_strcmp(argv[1], "here_doc") == 0)
	{
		pipex->first_cmd = 3;
		open_heredoc(pipex, argv[2]);
		open_outfile(pipex, argv[argc - 1], O_APPEND);
	}
	else
	{
		pipex->first_cmd = 2;
		open_infile(pipex, argv[1]);
		open_outfile(pipex, argv[argc - 1], O_TRUNC);
	}
	if (pipex->last_cmd < pipex->first_cmd)
		terminate(pipex, EXIT_FAILURE, 0, NULL);
	if (pipe(pipex->pipes[0]) == -1 || pipe(pipex->pipes[1]) == -1)
		terminate(pipex, EXIT_FAILURE, errno, "pipex: pipe");
}
