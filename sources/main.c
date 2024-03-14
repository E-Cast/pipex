/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:28:18 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/14 17:55:22 by ecastong         ###   ########.fr       */
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
		my_safefree(utils->cmd_arr[index]);// free_cmd(utils->cmd_arr[index]);
	my_safefree(utils->cmd_arr);
	if (cmd)
		my_safefree(cmd);// free_cmd(cmd);
	exit(exit_code);
	(void) cmd;
}

void	get_fd(t_utils *utils, t_cmd *cmd, int index)
{
	int	pipe_fd[2];

	if (index == utils->first_cmd)
		cmd->fd[0] = utils->input_file;
	else
		cmd->fd[0] = utils->tmp_fd;
	if (index == utils->last_cmd)
		cmd->fd[1] = utils->output_file;
	else
	{
		if (pipe(pipe_fd) == -1)
			terminate(utils, cmd, EXIT_FAILURE);
		cmd->fd[1] = pipe_fd[1];
		utils->tmp_fd = pipe_fd[0];
	}
}

t_cmd	*build_cmd(t_utils *utils, int cmd_index, char **argv)
{
	t_cmd	*cmd;
	int		index;

	cmd = ft_calloc(1, sizeof(cmd));
	if (cmd == NULL)
		terminate(utils, cmd, EXIT_FAILURE);
	index = utils->first_cmd + cmd_index;
	cmd->args = ft_split(argv[index], ' ');//place holder
	if (cmd->args == NULL)
		terminate(utils, cmd, EXIT_FAILURE);
	cmd->path = get_path(utils, cmd->args[0]);
	if (cmd->path == NULL)
		terminate(utils, cmd, EXIT_FAILURE);
	get_fd(utils, cmd, index);
	return (cmd);
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
}
