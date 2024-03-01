/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:45:15 by ecast             #+#    #+#             */
/*   Updated: 2024/03/01 06:33:03 by ecast            ###   ########.fr       */
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

// typedef struct s_cmd
// {
// 	char	*path;
// 	char	**args;
// 	pid_t	pid;
// }	t_cmd;

// typedef struct s_pipex
// {
// 	t_cmd	**cmd_arr;
// 	char	**envp;
// }	t_pipex;

void	close_all(t_pipex *pipex)
{
	if (pipex->input_file != -1)
		close(pipex->input_file);
	if (pipex->output_file != -1)
		close(pipex->output_file);
	if (pipex->pipes[0][1] != -1)
		close(pipex->pipes[0][1]);
	if (pipex->pipes[0][0] != -1)
		close(pipex->pipes[0][0]);
	if (pipex->pipes[1][1] != -1)
		close(pipex->pipes[1][1]);
	if (pipex->pipes[1][0] != -1)
		close(pipex->pipes[1][0]);
	pipex->input_file = -1;
	pipex->output_file = -1;
	pipex->pipes[0][1] = -1;
	pipex->pipes[0][0] = -1;
	pipex->pipes[1][1] = -1;
	pipex->pipes[1][0] = -1;
}

// void	free_cmd(t_cmd *cmd_arr)
// {
// 	int	index;

// 	index = 0;
// 	while (cmd_arr[index] != NULL)
// 	{
// 		waitpid(cmd_arr->);
// 		index++;
// 	}
// }

// void	terminate(t_pipex *pipex, int code)
// {
// 	int	index;

// 	close_all(pipex);
// 	if (pipex->cmd_arr)
// 	{
// 		//wait all pid
// 		//free every cmd
// 		//free 
// 	}
	
// 	exit(code);
// }

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 4)
		exit(1);//terminate
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (pipex == NULL)
		exit(1);//terminate
	open_fds(pipex, argc, argv);
	make_cmd_arrays(pipex, argv);
	pipex->envp = envp;
	exec_pipex(pipex);
	exit(pipex->exit_code);
}
