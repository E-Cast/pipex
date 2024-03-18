/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:03:07 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/18 00:46:41 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(t_arr arr, int index, char **envp, int cmd_count)
{
	dup2(arr.inputs[index], STDIN_FILENO);
	dup2(arr.outputs[index], STDOUT_FILENO);
	close_fd_arr(arr);
	if (arr.paths[index][0] == '\0')
	{
		ft_putstr_fd(arr.args[index][0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	execve(arr.paths[index], arr.args[index], envp);
	free_arr(arr, cmd_count);
	exit(EXIT_FAILURE);
}

int	wait_all(t_arr arr, int cmd_count)
{
	int	index;
	int	status;

	index = 0;
	while (index < cmd_count)
	{
		if (arr.pids[index] != 0)
			waitpid(arr.pids[index], &status, 0);
		index++;
	}
	return (status);
}

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

int	main(int argc, char **argv, char **envp)
{
	t_arr	arr;
	int		exit_code;

	(void) argc;
	if (init_arr(&arr, argv, envp) == EXIT_FAILURE)
	{
		free_arr(arr, get_cmd_count(argv));
		return (EXIT_FAILURE);
	}
	exit_code = exec_all(arr, get_cmd_count(argv), envp);
	free_arr(arr, get_cmd_count(argv));
	return (exit_code);
}
