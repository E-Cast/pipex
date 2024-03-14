/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:28:18 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/14 17:18:38 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	terminate(t_utils *utils, int exit_code)
{
	int	index;

	close(utils->input_file);
	close(utils->output_file);
	index = 0;
	while (utils->env_path && utils->env_path[index])
		my_safefree(utils->env_path[index++]);
	my_safefree(utils->env_path);
	index = 0;
	exit(exit_code);
}

t_cmd	*build_cmd(t_utils *utils, int cmd_index, char **argv)
{
	t_cmd	*cmd;
	int		index;

	cmd = ft_calloc(1, sizeof(cmd));
	if (cmd == NULL)
		terminate(utils, EXIT_FAILURE);
	index = utils->first_cmd + cmd_index;
	cmd->args = ft_split(argv[index], ' ');//place holder
	if (cmd->args == NULL)
		terminate(utils, EXIT_FAILURE);
	cmd->path = get_path(utils, cmd->args[0]);
	if (cmd->path == NULL)
		terminate(utils, EXIT_FAILURE);
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
		terminate(&utils, EXIT_FAILURE);
	utils.env_path = get_env_path(envp);
	cmd_count = utils.last_cmd - (utils.first_cmd - 1);
	utils.cmd_arr = ft_calloc(cmd_count + 1, sizeof(t_cmd *));
	if (utils.cmd_arr == NULL || utils.env_path == NULL)
		terminate(&utils, EXIT_FAILURE);
	index = 0;
	while (index < cmd_count)
	{
		utils.cmd_arr[index] = build_cmd(&utils, index, argv);
		if (utils.cmd_arr[index] == NULL)
			terminate(&utils, EXIT_FAILURE);
		printf("%s\n", utils.cmd_arr[index]->args[0]);
		printf("%s\n", utils.cmd_arr[index]->path);
		index++;
	}
}
