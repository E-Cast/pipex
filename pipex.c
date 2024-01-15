/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:17:26 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/15 07:31:56 by ecastong         ###   ########.fr       */
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

// void	close_unused_fd(t_fd fd)
// {
	
// }

// t_fd	fd_get_used(t_fd fd)
// {
	
// 	return (fd);
// }

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
			if (counter == 2)
			{
				fd.input = fd.infile;
				close(fd.outfile);
			}
			else if (counter % 2)
			{
				fd.input = fd.pipe1[0];
				close(fd.pipe1[1]);
			}
			else
			{
				fd.input = fd.pipe2[0];
				close(fd.pipe2[1]);
			}
			if (counter + 1 == argc -1)
			{
				fd.output = fd.outfile;
				close(fd.infile);
			}
			else if (counter % 2)
			{
				fd.output = fd.pipe2[1];
				close(fd.pipe2[0]);
			}
			else
			{
				fd.output = fd.pipe1[1];
				close(fd.pipe1[0]);
			}
			execute(fd.input, fd.output, argv[counter]);
			exit(EXIT_FAILURE);
		}
		counter++;
	}
	close(fd.pipe1[0]);
	close(fd.pipe1[1]);
	close(fd.pipe2[0]);
	close(fd.pipe2[1]);
	close(fd.outfile);
	close(fd.infile);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}

// < infile grep a1 | wc -w > outfile
/* Open infile, if no infile exists return an error. Open outfile, if it 
doesn't exist create it as a blank file. Check that all the commands exist and are valid.
Redirect infile to stdin and 
outfile to stdout.
	run grep a1 on it, */