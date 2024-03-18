/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:11:57 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/18 02:31:48 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Frees arr and all the arrays in it.
 * 
 * @param arr Array to be freed.
 * @param arr_length Length of the arrays in arr.
 */
void	free_arr(t_arr arr, int arr_length)
{
	int	index;

	if (arr.inputs || arr.outputs)
	{
		close_fd_arr(arr);
		arr.inputs = my_safefree(arr.inputs);
		arr.outputs = my_safefree(arr.outputs);
	}
	index = 0;
	while (index < arr_length)
	{
		if (arr.args)
			free_args(arr.args[index]);
		if (arr.paths)
			my_safefree(arr.paths[index]);
		index++;
	}
	if (arr.args)
		arr.args = my_safefree(arr.args);
	if (arr.paths)
		arr.paths = my_safefree(arr.paths);
	if (arr.pids)
		arr.pids = my_safefree(arr.pids);
}

/**
 * @brief Initializes the array and fills it.
 * 
 * @param arr Array to be initialized.
 * @param argv Arguments received by pipex.
 * @param envp Environment pointer.
 * @retval EXIT_FAILURE on failure.
 * @retval EXIT_SUCCESS on success.
 */
int	init_arr(t_arr *arr, char **argv, char **envp)
{
	int	cmd_count;
	int	first_cmd;
	int	index;

	if (get_fd_arr(arr, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cmd_count = get_cmd_count(argv);
	arr->args = ft_calloc(cmd_count + 1, sizeof(char **));
	arr->paths = ft_calloc(cmd_count + 1, sizeof(char *));
	arr->pids = ft_calloc(cmd_count + 1, sizeof(pid_t));
	if (arr->args == NULL || arr->paths == NULL || arr->pids == NULL)
		return (EXIT_FAILURE);
	first_cmd = get_first_cmd(argv);
	index = 0;
	while (index < cmd_count)
	{
		arr->args[index] = get_args(argv[first_cmd + index]);
		if (arr->args[index] == NULL)
			return (EXIT_FAILURE);
		arr->paths[index] = get_path(arr->args[index][0], envp);
		if (arr->paths[index] == NULL)
			return (EXIT_FAILURE);
		index++;
	}
	return (EXIT_SUCCESS);
}
