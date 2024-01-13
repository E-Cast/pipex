/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:17:26 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/13 02:46:39 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	execute(int infile, int outfile, char **argv)
{
	char	**args;
	char	*path;
	int		i;

	args = split_string(argv[2]);
	path = concat("/bin/", args[0]);
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
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
	int		infile;
	int		outfile;

	if (argc < 3)
		return (0);
	infile = open(argv[1], O_RDONLY | __O_CLOEXEC);
	if (infile == -1)
		exit(EXIT_FAILURE);
	outfile = open(argv[argc - 1], \
		O_CREAT | O_TRUNC | O_WRONLY | __O_CLOEXEC, 0644);
	if (outfile == -1)
	{
		close(infile);
		exit(EXIT_FAILURE);
	}
	execute(infile, outfile, argv);
	close(infile);
	close(outfile);
}

// < infile grep a1 | wc -w > outfile
/* Open infile, if no infile exists return an error. Open outfile, if it 
doesn't exist create it as a blank file. Check that all the commands exist and are valid.
Redirect infile to stdin and 
outfile to stdout.
	run grep a1 on it, */