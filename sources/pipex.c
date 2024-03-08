/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:07:46 by ecast             #+#    #+#             */
/*   Updated: 2024/03/07 21:05:28 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_pipes(t_pipex *pipex)
{
	int	count;
	int	index;

	count = pipex->last_cmd - pipex->first_cmd;
	pipex->p_arr = ft_calloc(count, sizeof(int [2]));
	if (pipex->p_arr == NULL)
		terminate(pipex, EXIT_FAILURE, errno, "pipex: ft_calloc");
	index = 0;
	while (index < count)
		if (pipe(pipex->p_arr[index++]) == -1)
			terminate(pipex, EXIT_FAILURE, errno, "pipex: pipe");
}

/*Finds and returns the needed input file descriptor.*/
int	get_input(t_pipex *pipex, int index)
{
	if (index == 0)
		return (pipex->input_file);
	else
		return (pipex->p_arr[index - 1][0]);
}

/*Finds and returns the needed output file descriptor.*/
int	get_output(t_pipex *pipex, int index)
{
	if (pipex->args[index + 1] == NULL)
		return (pipex->output_file);
	else
		return (pipex->p_arr[index][1]);
}

/*Executes the command whose args and path are located 
	at the index using the specified file descriptors.*/
void	exec_cmd(t_pipex *pipex, int index, int input, int output)
{
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
	close_all(pipex);
	execve(pipex->path[index], pipex->args[index], pipex->envp);
	exit(1);
}

/*Executes every command stored in the args and path arrays the returns.*/
int	exec_pipex(t_pipex *pipex)
{
	int	index;
	int	input;
	int	output;

	open_pipes(pipex);
	index = 0;
	while (pipex->args[index])
	{
		input = get_input(pipex, index);
		output = get_output(pipex, index);
		pipex->pid[index] = fork();
		if (pipex->pid[index] == -1)
			terminate(pipex, EXIT_FAILURE, errno, "pipex: fork");
		if (pipex->pid[index] == 0)
			exec_cmd(pipex, index, input, output);
		index++;
	}
	return (free_all(pipex));
}
