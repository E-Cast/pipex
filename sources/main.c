/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:03:07 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/18 02:02:55 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_arr	arr;
	int		cmd_count;
	int		exit_code;

	if (argc < 5)
	{
		ft_putendl_fd("pipex: needs four arguments or more.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	cmd_count = get_cmd_count(argv);
	if (cmd_count == 0)
	{
		close(get_input_fd(argv));
		close(get_output_fd(argv));
		return (EXIT_FAILURE);
	}
	if (init_arr(&arr, argv, envp) == EXIT_FAILURE)
	{
		free_arr(arr, cmd_count);
		return (EXIT_FAILURE);
	}
	exit_code = exec_all(arr, cmd_count, envp);
	free_arr(arr, cmd_count);
	return (exit_code);
}
