/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:17:26 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/13 01:13:49 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int		infile;
	int		outfile;
	char	**args;
	char	*path;

	if (argc < 3)
		return (0);
	infile = open(argv[1], O_RDONLY | O_CLOEXEC);
	if (infile == -1)
	{
		close(infile);
		exit(EXIT_FAILURE);
	}
	outfile = open(argv[argc - 1], \
		O_CREAT | O_TRUNC | O_WRONLY | O_CLOEXEC, 0644);
	if (outfile == -1)
	{
		close(infile);
		close(outfile);
		exit(EXIT_FAILURE);
	}
	args = split_string(argv[2]);
	char *const envp[] = {NULL};
	path = concat("/bin/", args[0]);
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execve(path, args, envp);
	close(infile);
	close(outfile);
}

// < infile grep a1 | wc -w > outfile
/* Open infile, if no infile exists return an error. Open outfile, if it 
doesn't exist create it as a blank file. Check that all the commands exist and are valid.
Redirect infile to stdin and 
outfile to stdout.
	run grep a1 on it, */