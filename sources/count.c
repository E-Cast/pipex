/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:16:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/18 00:36:28 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Get the index of the first valid command in argv.
 * 
 * @param argv Arguments received by pipex.
 * @retval Index of the first valid command.
 */
int	get_first_cmd(char **argv)
{
	if (my_strcmp(argv[1], "here_doc") == 0)
		return (3);
	else if (access(argv[1], R_OK) == 0)
		return (2);
	else
		return (3);
}

/**
 * @brief Get the number of valid commands.
 * 
 * @param argv Arguments received by pipex.
 * @retval Number of valid commands.
 */
int	get_cmd_count(char **argv)
{
	int	first_cmd;
	int	index;

	first_cmd = get_first_cmd(argv);
	index = first_cmd;
	while (argv[index + 1] != NULL)
		index++;
	if (access(argv[index], W_OK) == 0 || errno == ENOENT)
		return ((index - first_cmd));
	else
		return ((index - first_cmd) - 1);
}
