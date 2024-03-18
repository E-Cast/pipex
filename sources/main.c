/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:03:07 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/17 21:18:48 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fill_arr(t_arr *arr, char **argv, char **envp)
{
	// int		cmd_count;
	// int		first_cmd;
	// int		index;

	if (get_fd_arr(arr, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// cmd_count = get_cmd_count(argv);
	// arr.paths = ft_calloc(cmd_count + 1, sizeof(char *));
	// arr.args = ft_calloc(cmd_count + 1, sizeof(char **));
	// arr.pids = ft_calloc(cmd_count + 1, sizeof(pid_t));
	// if (!arr.inputs || !arr.outputs || !arr.paths || !arr.args || arr.pids)
	// 	return (free_arr());
	// first_cmd = get_first_cmd();
	// index = 0;
	// while (index < cmd_count)
	// {
	// 	index++;
	// }
	(void) envp;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_arr	arr;

	fill_arr(&arr, argv, envp);
	(void) argc;
	int index = 0;
	while (arr.inputs[index])
	{
		printf("index:%i\ninput:%i\noutput:%i\n\n",
			index, arr.inputs[index], arr.outputs[index]);
		index++;
	}
}
