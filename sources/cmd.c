/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:30:52 by ecast             #+#    #+#             */
/*   Updated: 2024/03/01 07:47:37 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_cmd(t_pipex *pipex, int index, char *argstr)
{
	pipex->args[index] = ft_split(argstr, ' '); //placeholder
	if (pipex->args[index] == NULL)
		terminate(pipex, EXIT_FAILURE);//terminate
	pipex->path[index] = ft_strjoin("/usr/bin/", pipex->args[index][0]);
	if (pipex->path[index] == NULL)
		terminate(pipex, EXIT_FAILURE);//terminate
}

void	make_cmd_arrays(t_pipex *pipex, char **argv)
{
	int	cmd_count;
	int	argv_index;
	int	arr_index;

	cmd_count = pipex->last_cmd - (pipex->first_cmd - 1);
	pipex->args = ft_calloc(cmd_count + 1, sizeof(char **));
	if (pipex->args == NULL)
		terminate(pipex, EXIT_FAILURE);//terminate
	pipex->path = ft_calloc(cmd_count + 1, sizeof(char *));
	if (pipex->path == NULL)
		terminate(pipex, EXIT_FAILURE);//terminate
	pipex->pid = ft_calloc(cmd_count + 1, sizeof(char *));
	if (pipex->pid == NULL)
		terminate(pipex, EXIT_FAILURE);//terminate
	argv_index = pipex->first_cmd;
	arr_index = 0;
	while (argv_index <= pipex->last_cmd)
	{
		make_cmd(pipex, arr_index, argv[argv_index]);
		arr_index++;
		argv_index++;
	}
}
