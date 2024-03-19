/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:47:39 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/19 14:36:52 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Executes the command stored at position index in the arr struct.
 * 
 * @param arr Struct containing every command.
 * @param index Index of the command to execute.
 * @param envp Environment pointer.
 * @param cmd_count Number of commands.
 */
void	exec_cmd(t_arr arr, int index, char **envp, int cmd_count)
{
	dup2(arr.inputs[index], STDIN_FILENO);
	dup2(arr.outputs[index], STDOUT_FILENO);
	close_fd_arr(arr);
	if (ft_strchr(arr.args[index][0], '/') != NULL)
	{
		if (access(arr.args[index][0], X_OK) != 0)
		{
			ft_putstr_fd("pipex: ", STDERR_FILENO);
			ft_putstr_fd(arr.args[index][0], STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		}
		execve(arr.args[index][0], arr.args[index], envp);
	}
	else if (arr.paths[index][0] == '\0')
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(arr.args[index][0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else
		execve(arr.paths[index], arr.args[index], envp);
	free_arr(arr, cmd_count);
	exit(EXIT_FAILURE);
}

/**
 * @brief Waits for every child process to end.
 * 
 * @param arr Struct containing every pid.
 * @param cmd_count Number of commands.
 * @retval Exit code of the last command.
 */
int	wait_all(t_arr arr, int cmd_count)
{
	int	index;
	int	status;

	index = 0;
	status = 0;
	while (index < cmd_count)
	{
		if (arr.pids[index] != 0)
			waitpid(arr.pids[index], &status, 0);
		index++;
	}
	return (status);
}

/**
 * @brief Executes every command stored in the arr struct.
 * 
 * @param arr Struct containing every command's information.
 * @param cmd_count Number of commands.
 * @param envp Environment pointer.
 * @retval EXIT_FAILURE on failure.
 * @retval Exit code of the last command on success.
 */
int	exec_all(t_arr arr, int cmd_count, char **envp)
{
	int	index;

	index = 0;
	while (arr.args[index])
	{
		arr.pids[index] = fork();
		if (arr.pids[index] == -1)
			return (EXIT_FAILURE);
		if (arr.pids[index] == 0)
			exec_cmd(arr, index, envp, cmd_count);
		index++;
	}
	close_fd_arr(arr);
	return (wait_all(arr, cmd_count));
}
