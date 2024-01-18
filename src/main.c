/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 06:34:27 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/18 10:23:53 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"


t_fd	open_files(t_fd fd, int argc, char **argv)
{
	fd.infile = open(argv[1], O_RDONLY);
	if (fd.infile == -1 && (errno == ENOENT || errno == EACCES))
	{
		perror(argv[1]);
		fd.infile = open("/dev/null", O_RDONLY);
	}
	if (fd.infile == -1)
	{
		perror(argv[argc - 1]);
		exit(EXIT_FAILURE);
	}
	fd.outfile = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (fd.outfile == -1 && errno == EACCES)
	{
		perror(argv[argc - 1]);
		fd.outfile = open("/dev/null", O_WRONLY);
	}
	if (fd.outfile == -1)
	{
		perror(argv[argc - 1]);
		close(fd.infile);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

t_fd	open_pipes(t_fd fd)
{
	if (pipe(fd.pipe1) == -1)
	{
		close_unused(fd, -1, -1);
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd.pipe2) == -1)
	{
		close_unused(fd, -1, -1);
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	return (fd);
}

void	close_unused(t_fd fd, int used1, int used2)
{
	if (fd.infile != used1 && fd.infile == used2)
		close(fd.infile);
	if (fd.outfile != used1 && fd.outfile == used2)
		close(fd.outfile);
	if (fd.pipe1[0] != used1 && fd.pipe1[0] == used2)
		close(fd.pipe1[0]);
	if (fd.pipe1[1] != used1 && fd.pipe1[1] == used2)
		close(fd.pipe1[1]);
	if (fd.pipe2[0] != used1 && fd.pipe2[0] == used2)
		close(fd.pipe2[0]);
	if (fd.pipe2[1] != used1 && fd.pipe2[1] == used2)
		close(fd.pipe2[1]);
	if (fd.input != used1 && fd.input == used2)
		close(fd.input);
	if (fd.output != used1 && fd.output == used2)
		close(fd.output);
}

int	main(int argc, char **argv)
{
	t_fd	fd;
	int		*pid;
	int		index;

	if (argc < 3)
		return (0);
	fd = open_files(fd, argc, argv);
	fd = open_pipes(fd);
	pid = ft_calloc(argc - 2, sizeof(int));
	if (!pid)
	{
		close_unused(fd, -1, -1);
		exit(EXIT_FAILURE);
	}
	// index = 2;
	// while (index < argc - 1)
	// {
	// 	fd = get_used(fd, argc, index);
	// 	pid[index - 2] = execute(fd, argv, index++);
	// }
	// close_unused(fd, -1, -1);
	// wait_all(pid);
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
		permissions missing: Run the cmds with /dev/null as final output. Error "bash: filename: Permission denied"
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