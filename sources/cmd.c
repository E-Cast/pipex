/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:29:54 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/14 18:54:22 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		terminate(utils, cmd, EXIT_FAILURE);
	index = utils->first_cmd + cmd_index;
	cmd->args = ft_split(argv[index], ' ');//pholder
	if (cmd->args == NULL)
		terminate(utils, cmd, EXIT_FAILURE);
	cmd->path = get_path(utils, cmd->args[0]);
	if (cmd->path == NULL)
		terminate(utils, cmd, EXIT_FAILURE);
	get_fd(utils, cmd, index);
	return (cmd);
}

void	*free_cmd(t_cmd *cmd)
{
	int	index;

	if (cmd == NULL)
		return (NULL);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	//need to add a wait for the pid
	cmd->path = my_safefree(cmd->path);
	index = 0;
	while (cmd->args && cmd->args[index])
	{
		cmd->args[index] = my_safefree(cmd->args[index]);
		index++;
	}
	cmd->args = my_safefree(cmd->args);
	cmd = my_safefree(cmd);
	return (cmd);
}
