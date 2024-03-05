/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 07:38:11 by ecast             #+#    #+#             */
/*   Updated: 2024/03/05 07:54:53 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	wait_all(t_pipex *pipex)
{
	int	index;
	int	status;

	index = 0;
	while (pipex->args && pipex->args[index])
	{
		if (pipex->pid[index] != 0)
			waitpid(pipex->pid[index], &status, 0);
		index++;
	}
	return (status);
}

void	free_all(t_pipex *pipex)
{
	int	index;
	int	index_2;

	close_all(pipex);
	wait_all(pipex);
	my_safefree(pipex->pid);
	index = 0;
	while (pipex->path && pipex->path[index])
		my_safefree(pipex->path[index++]);
	my_safefree(pipex->path);
	index = 0;
	while (pipex->args && pipex->args[index])
	{
		index_2 = 0;
		while (pipex->args[index] && pipex->args[index][index_2])
			my_safefree(pipex->args[index][index_2++]);
		my_safefree(pipex->args[index]);
		index++;
	}
	my_safefree(pipex->args);
	my_safefree(pipex);
}

void	terminate(t_pipex *pipex, int exit_code, int error, char *prefix)
{
	free_all(pipex);
	if (prefix != NULL)
	{
		errno = error;
		perror(prefix);
	}
	exit(exit_code);
}
