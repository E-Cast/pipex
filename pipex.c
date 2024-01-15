/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:17:26 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/15 06:58:56 by ecastong         ###   ########.fr       */
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

// int	main(int argc, char **argv)
// {
// 	int		infile;
// 	int		outfile;
// 	int		pipe_fd1[2];
// 	int		pipe_fd2[2];
// 	pid_t	pid1;
// 	pid_t	pid2;


// 	if (argc < 3)
// 		return (0);
// 	infile = open(argv[1], O_RDONLY | __O_CLOEXEC);
// 	if (infile == -1)
// 		exit(EXIT_FAILURE);
/* 	outfile = open(argv[argc - 1], \
 		O_CREAT | O_TRUNC | O_WRONLY | __O_CLOEXEC, 0644);*/
// 	if (outfile == -1)
// 	{
// 		close(infile);
// 		exit(EXIT_FAILURE);
// 	}
	
// 	if (pipe(pipe_fd1) == -1 || pipe(pipe_fd2) == -1)
// 		exit(EXIT_FAILURE);
// 	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		close(pipe_fd1[0]);
// 		close(outfile);
// 		execute(infile, pipe_fd1[1], argv[2]);
// 	}
// 	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		close(pipe_fd1[1]);
// 		close(infile);
// 		execute(pipe_fd1[0], outfile, argv[3]);
// 	}
// 	close(pipe_fd1[0]);
// 	close(pipe_fd1[1]);
// 	close(pipe_fd2[0]);
// 	close(pipe_fd2[1]);
// 	close(outfile);
// 	close(infile);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// }

int	main(int argc, char **argv)
{
	t_fd	fd;
	pid_t	pid1;
	pid_t	pid2;


	if (argc < 3)
		return (0);
	fd.input = open(argv[1], O_RDONLY | __O_CLOEXEC);
	if (fd.input == -1)
		exit(EXIT_FAILURE);
	fd.output = open(argv[argc - 1], \
		O_CREAT | O_TRUNC | O_WRONLY | __O_CLOEXEC, 0644);
	if (fd.output == -1)
	{
		close(fd.input);
		exit(EXIT_FAILURE);
	}
	
	if (pipe(fd.pipe1) == -1 || pipe(fd.pipe2) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd.pipe1[0]);
		close(fd.output);
		execute(fd.input, fd.pipe1[1], argv[2]);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(fd.pipe1[1]);
		close(fd.input);
		execute(fd.pipe1[0], fd.output, argv[3]);
	}
	close(fd.pipe1[0]);
	close(fd.pipe1[1]);
	close(fd.pipe2[0]);
	close(fd.pipe2[1]);
	close(fd.output);
	close(fd.input);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

// < infile grep a1 | wc -w > outfile
/* Open infile, if no infile exists return an error. Open outfile, if it 
doesn't exist create it as a blank file. Check that all the commands exist and are valid.
Redirect infile to stdin and 
outfile to stdout.
	run grep a1 on it, */