/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:28:18 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/14 12:23:24 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	terminate(t_utils *utils, int exit_code)
{
	close(utils->input_file);
	close(utils->output_file);
	exit(exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	utils.input_file = open_input(argv, &utils.first_cmd);
	utils.output_file = open_output(argc, argv, &utils.last_cmd);
	if (utils.output_file == -1)
		terminate(&utils, EXIT_FAILURE);
	(void) envp;
}
