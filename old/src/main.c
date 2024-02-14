/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 06:34:27 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/25 09:20:48 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	execute(t_fd fd, char *argstr)
{
	char	**args;
	char	*path;
	int		index;

	args = split_string(argstr);
	path = concat("/bin/", args[0]);
	dup2(fd.input, STDIN_FILENO);
	dup2(fd.output, STDOUT_FILENO);
	close_unused(fd, -1, -1);
	execve(path, args, NULL);
	free(path);
	index = 0;
	while (args[index] != NULL)
	{
		free(args[index]);
		index++;
	}
	free(args);
}

void	wait_all(pid_t *pid)
{
	int	index;
	int	status;

	index = 0;
	while (pid[index])
	{
		waitpid(pid[index], &status, 0);
		index++;
	}
}

int	main(int argc, char **argv)
{
	t_fd	fd;
	pid_t	pid[10];
	int		index;

	fd = open_files(fd, argc, argv);
	fd = open_pipes(fd);
	index = 2;
	while (index < argc - 1)
	{
		pid[index - 2] = fork();
		if (pid[index - 2] == 0)
		{
			fd = get_used(fd, index, argc);
			execute(fd, argv[index]);
		}
		index++;
	}
	wait_all(pid);
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