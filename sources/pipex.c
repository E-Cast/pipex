/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:07:46 by ecast             #+#    #+#             */
/*   Updated: 2024/03/01 08:27:33 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_input(t_pipex *pipex, int index)
{
	int	input;

	if (index == 0)
		input = pipex->input_file;
	else if ((index % 2) == 1)
		input = pipex->pipes[0][0];
	else
		input = pipex->pipes[1][0];
	return (input);
}

int	get_output(t_pipex *pipex, int index)
{
	int	output;

	if (pipex->args[index + 1] == NULL)
		output = pipex->output_file;
	else if ((index % 2) == 0)
		output = pipex->pipes[0][1];
	else
		output = pipex->pipes[1][1];
	return (output);
}

void	exec_cmd(t_pipex *pipex, int index, int input, int output)
{
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close_all(pipex);
	execve(pipex->path[index], pipex->args[index], pipex->envp);
	exit(1);
}

void	exec_pipex(t_pipex *pipex)
{
	int	index;
	int	input;
	int	output;

	index = 0;
	while (pipex->args[index])
	{
		input = get_input(pipex, index);
		output = get_output(pipex, index);
		pipex->pid[index] = fork();
		if (pipex->pid[index] == -1)
			terminate(pipex, EXIT_FAILURE);//terminate
		if (pipex->pid[index] == 0)
			exec_cmd(pipex, index, input, output);
		index++;
	}
	close_all(pipex);
	wait_all(pipex);
}
