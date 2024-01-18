/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:17:26 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/18 06:34:15 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

	fd = fd_open_all(fd, argc, argv);
	counter = 2;
	while (counter < argc - 1)
	{
		pid[counter - 2] = fork();
		if (pid[counter - 2] == 0)
		{
			fd = fd_get_used(fd, counter, argc);
			fd_close_unused(fd, fd.input, fd.output);
			execute(fd.input, fd.output, argv[counter]);
			exit(EXIT_FAILURE);
		}
		counter++;
	}
	fd_close_unused(fd, -1, -1);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}
