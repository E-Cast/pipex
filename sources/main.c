/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:28:18 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/14 19:08:32 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	terminate(t_utils *utils, t_cmd *cmd, int exit_code)
{
	int	index;

	close(utils->input_file);
	close(utils->output_file);
	close(utils->tmp_fd);
	index = 0;
	while (utils->env_path && utils->env_path[index])
		my_safefree(utils->env_path[index++]);
	my_safefree(utils->env_path);
	index = 0;
	while (utils->cmd_arr && utils->cmd_arr[index])
		free_cmd(utils->cmd_arr[index++]);
	my_safefree(utils->cmd_arr);
	if (cmd)
		free_cmd(cmd);
	exit(exit_code);
	(void) cmd;
}

void	close_all(t_utils *utils)
{
	t_cmd	**arr;
	int 	index;

	close(utils->input_file);
	close(utils->output_file);
	close(utils->tmp_fd);
	arr = utils->cmd_arr;
	index = 0;
	while (arr[index])
	{
		close(arr[index]->fd[0]);
		close(arr[index]->fd[1]);
		index++;
	}
}

void	exec_cmd(t_utils *utils, t_cmd *cmd, char **envp)
{
	dup2(cmd->fd[0], STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	close_all(utils);
	execve(cmd->path, cmd->args, envp);
	terminate(utils, cmd, EXIT_FAILURE);
}

void	exec_all(t_utils *utils, t_cmd **cmd_arr, char **envp)
{
	int	index;
	// int	status;

	index = 0;
	while (cmd_arr[index])
	{
		if (fork() == 0)
			exec_cmd(utils, cmd_arr[index], envp);
		index++;
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;
	int		cmd_count;
	int		index;

	utils.input_file = open_input(argv, &utils.first_cmd);
	utils.output_file = open_output(argc, argv, &utils.last_cmd);
	if (utils.input_file == -1 || utils.output_file == -1)
		terminate(&utils, NULL, EXIT_FAILURE);
	utils.env_path = get_env_path(envp);
	cmd_count = utils.last_cmd - (utils.first_cmd - 1);
	utils.cmd_arr = ft_calloc(cmd_count + 1, sizeof(t_cmd *));
	if (utils.cmd_arr == NULL || utils.env_path == NULL)
		terminate(&utils, NULL, EXIT_FAILURE);
	index = 0;
	while (index < cmd_count)
	{
		utils.cmd_arr[index] = build_cmd(&utils, index, argv);
		if (utils.cmd_arr[index] == NULL)
			terminate(&utils, NULL, EXIT_FAILURE);
		index++;
	}
	exec_all(&utils, utils.cmd_arr, envp);
	terminate(&utils, NULL, EXIT_SUCCESS);
}
