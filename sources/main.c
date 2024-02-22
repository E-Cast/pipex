/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:45:15 by ecast             #+#    #+#             */
/*   Updated: 2024/02/21 22:40:32 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_heredoc(t_pipex *pipex, char *limiter)
{
	int		hd_pipe[2];
	char	*input;

	if (pipe(hd_pipe) == -1)
		return ;//terminate
	input = get_next_line(STDIN_FILENO);
	while (input != NULL)
	{
		if (ft_strncmp(input, limiter, ft_strlen(input) - 1) == 0)
			break ;
		ft_putstr_fd(input, hd_pipe[0]);
		my_safefree(input);
		input = get_next_line(STDIN_FILENO);
	}
	my_safefree(input);
	close(hd_pipe[0]);
	pipex->input_file = hd_pipe[1];
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

void	init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (my_strcmp(argv[1], "here_doc") == 0)
	{
		open_heredoc(pipex, argv[2]);
		open_outfile(pipex, argv[argc - 1], O_APPEND);
	}
	else
	{
		open_infile(pipex, argv[1]);
		open_outfile(pipex, argv[argc - 1], O_TRUNC);
	}
	// get cmd count
	// alloc args and path accordingly
	// get paths and args for every cmd
	// put them into the paths and args array
	pipex->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	if (pipex == NULL)
		return (1);//terminate
	init(pipex, argc, argv, envp);
}
