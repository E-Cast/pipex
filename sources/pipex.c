/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:07:46 by ecast             #+#    #+#             */
/*   Updated: 2024/02/28 23:08:43 by ecast            ###   ########.fr       */
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

	if (pipex->cmd_arr[index + 1] == NULL)
		output = pipex->output_file;
	else if ((index % 2) == 0)
		output = pipex->pipes[0][1];
	else
		output = pipex->pipes[1][1];
	return (output);
}

void	exec_cmd(t_pipex *pipex, t_cmd *cmd, int infd, int outfd)
{
	dup2(infd, STDIN_FILENO);
	dup2(outfd, STDOUT_FILENO);
	close_all(pipex);
	execve(cmd->path, cmd->args, pipex->envp);
	exit(1);//terminate
}

void	exec_pipex(t_pipex *pipex)
{
	int	index;
	int	input;
	int	output;
	int	status;

	index = 0;
	while (pipex->cmd_arr[index])
	{
		input = get_input(pipex, index);
		output = get_output(pipex, index);
		pipex->cmd_arr[index]->pid = fork();
		if (pipex->cmd_arr[index]->pid == -1)
			exit(1);//terminate? error
		if (pipex->cmd_arr[index]->pid == 0)
			exec_cmd(pipex, pipex->cmd_arr[index], input, output);
		index++;
	}
	close_all(pipex);
	index = 0;
	while (pipex->cmd_arr[index])
	{
		waitpid(pipex->cmd_arr[index]->pid, &status, 0);
		index++;
	}
	exit(status);//terminate status
}
