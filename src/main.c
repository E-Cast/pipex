/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 06:34:27 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/18 08:48:44 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <errno.h>

// int	check_args()
// {
// 	check if it has an heredoc argument
// }

// void	bonus()
// {
// 	run pipex as bonus
// }

t_fd	open_files(t_fd fd, int argc, char **argv)
{
	if (access(argv[1], R_OK))
	{
		perror(argv[1]);
		fd.infile = open("/dev/null", O_RDONLY | __O_CLOEXEC);
	}
	else
		fd.infile = open(argv[1], O_RDONLY | __O_CLOEXEC);
	if (fd.infile == -1)
	{
		perror(argv[argc - 1]);
		exit(EXIT_FAILURE);
	}
	fd.outfile = open(argv[argc - 1], \
		O_CREAT | O_TRUNC | O_WRONLY | __O_CLOEXEC, 0664);
	if (fd.outfile == -1)
	{
		close(fd.infile);
		perror(argv[argc - 1]);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

t_fd	open_pipes(t_fd fd)
{
	if (pipe(fd.pipe1) == -1)
	{
		close(fd.infile);
		close(fd.outfile);
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd.pipe2) == -1)
	{
		close(fd.infile);
		close(fd.outfile);
		close(fd.pipe1[0]);
		close(fd.pipe1[1]);
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	return (fd);
}

int	main(int argc, char **argv)
{
	t_fd	fd;

	fd = open_files(fd, argc, argv);
	fd = open_pipes(fd);
	// if (check_args() == bonus)
	// 	here_doc();
	// else
	// 	pipex();
}

/*
Files tests:
	cmd:
		< infile grep test | tee thirdfile | wc -l > outfile
	infile:
		valid: Run commands with it as first input.
		nonexistant: Run commands with no input. Error: "bash: filename: No such file or directory"
		permissions missing: Run commands with no input. Error: "bash: filename: Permission denied"
		not a text file: Run commands with no input/Undefined behavior?
	outfile:
		valid: Send final output to it.
		nonexistant: Create it and send final output to it.
		permissions missing: Don't run the cmds. Error "bash: filename: Permission denied"
		not a text file: Run commands and output them to it, turning it into a text file.
Cmd tests:
	invalid cmd:
		< infile grep test | tee thirdfile | invalidcmd | tee fourthfile | wc -l > outfile
	behavior:
		Still runs every commands in the chain no matter where the cmd is in it.
		Error "invalidcmd: command not found"
		or
		Command 'invalidcmd' not found, did you mean:
			command 'example1' from deb source
			command 'example2' from deb source
			command 'example3' from deb source
			command 'example4' from deb source
	cmd failed:
		< infile grep test | tee thirdfile | grep test | tee fourthfile | wc -l > outfile
	behavior:
		when called with either thirdfile or fourthile at 0 permissions, it fails to run that specific command but continues the chain.
		Error "tee: filename: Permission denied"
*/