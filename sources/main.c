/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:03:07 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/18 00:55:28 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
