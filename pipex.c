/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:17:26 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/15 07:39:20 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(int input, int output, char *string)
{
	char	**args;
	char	*path;
	int		i;

	args = split_string(string);
	path = concat("/bin/", args[0]);
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close(input);
	close(output);
	execve(path, args, NULL);
	if (path)
		free(path);
	i = 0;
	while (args[i])
	{
		if (args[i])
			free(args[i]);
		i++;
	}
	free(args);
}

int	main(int argc, char **argv)
{
	t_fd	fd;
	pid_t	pid[2];
	int		counter;


	if (argc < 3)
		return (0);
	fd.infile = open(argv[1], O_RDONLY | __O_CLOEXEC);
	if (fd.infile == -1)
		exit(EXIT_FAILURE);
	fd.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY | __O_CLOEXEC, 0644);
	if (fd.outfile == -1)
	{
		close(fd.infile);
		exit(EXIT_FAILURE);
	}
	
	counter = 2;
	if (pipe(fd.pipe1) == -1 || pipe(fd.pipe2) == -1)
		exit(EXIT_FAILURE);
	while (counter < argc - 1)
	{
		pid[counter - 2] = fork();
		if (pid[counter - 2] == 0)
		{
			fd = fd_get_used(fd, counter, argc);
			fd_close_unused(fd);
			execute(fd.input, fd.output, argv[counter]);
			exit(EXIT_FAILURE);
		}
		counter++;
	}
	fd.input = -1;
	fd.output = -1;
	fd_close_unused(fd);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}
