/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:30:52 by ecast             #+#    #+#             */
/*   Updated: 2024/02/28 22:34:52 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*make_cmd(char *argstr)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		exit(1);//terminate
	cmd->args = ft_split(argstr, ' ');//placeholder
	if (cmd->args == NULL)
		exit(1);//terminate
	cmd->path = ft_strjoin("/usr/bin/", cmd->args[0]);
	if (cmd->path == NULL)
		exit(1);//terminate
	return (cmd);
}

void	make_cmd_array(t_pipex *pipex, char **argv)
{
	int	cmd_count;
	int	argv_index;
	int	arr_index;

	cmd_count = pipex->last_cmd - (pipex->first_cmd - 1);
	pipex->cmd_arr = ft_calloc(cmd_count + 1, sizeof(t_cmd *));
	if (pipex->cmd_arr == NULL)
		exit(1);//terminate
	argv_index = pipex->first_cmd;
	arr_index = 0;
	while (argv_index <= pipex->last_cmd)
	{
		pipex->cmd_arr[arr_index] = make_cmd(argv[argv_index]);
		if (pipex->cmd_arr[arr_index] == NULL)
			exit(1);//terminate
		arr_index++;
		argv_index++;
	}
}
