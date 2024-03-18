/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_arr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:18:41 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/18 00:36:46 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Closes every fd in both fd arrays and.
 * 
 * @param arr Struct containing every array for pipex.
 */
void	close_fd_arr(t_arr arr)
{
	int	index;

	index = 0;
	while (arr.inputs && arr.inputs[index] != 0)
		close(arr.inputs[index++]);
	index = 0;
	while (arr.outputs && arr.outputs[index] != 0)
		close(arr.outputs[index++]);
}

/**
 * @brief Allocates and fills both fd arrays in arr.
 * 
 * @param arr Struct containing every array for pipex.
 * @param argv Arguments received by pipex.
 * @retval EXIT_FAILURE on failure.
 * @retval EXIT_SUCCESS on success.
 */
int	get_fd_arr(t_arr *arr, char **argv)
{
	int		cmd_count;
	int		index;
	int		pipe_fd[2];

	cmd_count = get_cmd_count(argv);
	arr->inputs = ft_calloc(cmd_count + 1, sizeof(int));
	arr->outputs = ft_calloc(cmd_count + 1, sizeof(int));
	if (arr->inputs == NULL || arr->outputs == NULL)
		return (EXIT_FAILURE);
	index = 0;
	arr->inputs[0] = get_input_fd(argv);
	if (arr->inputs[0] == -1)
		return (EXIT_FAILURE);
	while (index + 1 < cmd_count)
	{
		if (pipe(pipe_fd) == -1)
			return (EXIT_FAILURE);
		arr->inputs[index + 1] = pipe_fd[0];
		arr->outputs[index] = pipe_fd[1];
		index++;
	}
	arr->outputs[cmd_count - 1] = get_output_fd(argv);
	if (arr->outputs[cmd_count - 1] == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
