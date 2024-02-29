/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:45:15 by ecast             #+#    #+#             */
/*   Updated: 2024/02/28 23:08:40 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <sys/types.h>
/*
./pipex "grep 'Hello \' World"
grep
'hello \'
world
*/
/*
./pipex 'grep "Hello \" World"'
grep
Hello " World
*/

void	close_all(t_pipex *pipex)
{
	close(pipex->input_file);
	close(pipex->output_file);
	close(pipex->pipes[0][1]);
	close(pipex->pipes[0][0]);
	close(pipex->pipes[1][1]);
	close(pipex->pipes[1][0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 4)
		exit(1);//terminate
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (pipex == NULL)
		exit(1);//terminate
	open_fds(pipex, argc, argv);
	make_cmd_array(pipex, argv);
	pipex->envp = envp;
	exec_pipex(pipex);
}
