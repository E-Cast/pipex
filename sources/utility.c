/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 07:38:11 by ecast             #+#    #+#             */
/*   Updated: 2024/03/07 21:02:08 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Closes every file descriptor stored in pipex and sets their value to -1.*/
void	close_all(t_pipex *pipex)
{
	int	index;

	if (pipex->input_file != -1)
		close(pipex->input_file);
	if (pipex->output_file != -1)
		close(pipex->output_file);
	pipex->input_file = -1;
	pipex->output_file = -1;
	index = (pipex->last_cmd - pipex->first_cmd) - 1;
	while (index > -1)
	{
		if (pipex->p_arr[index][0] != -1)
			close(pipex->p_arr[index][0]);
		if (pipex->p_arr[index][1] != -1)
			close(pipex->p_arr[index][1]);
		pipex->p_arr[index][0] = -1;
		pipex->p_arr[index][1] = -1;
		index--;
	}
}

/*Waits for every process stored in pipex to finish, 
	returns the status of the last process.*/
int	wait_all(t_pipex *pipex)
{
	int	index;
	int	status;

	index = 0;
	while (pipex->args && pipex->args[index])
	{
		printf("pid:%i\n", pipex->pid[index]);
		if (pipex->pid[index] != 0)
			waitpid(pipex->pid[index], &status, 0);
		index++;
	}
	return (status);
}

/*Calls close_all and wait_all then safely frees all 
	the dynamically allocated memory stored in pipex.
	Returns the status of the last pid if applicable.*/
int	free_all(t_pipex *pipex)
{
	int	index;
	int	index_2;
	int	status;

	close_all(pipex);
	status = wait_all(pipex);
	my_safefree(pipex->pid);
	index = 0;
	while (pipex->path && pipex->path[index])
		my_safefree(pipex->path[index++]);
	my_safefree(pipex->path);
	my_safefree(pipex->p_arr);
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
	return (status);
}

/*Calls free_all and then calls perror with the specified prefix 
	and errno if applicable, then exits with exit_code.*/
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
