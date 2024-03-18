/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:52:12 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/17 21:13:17 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Opens the output fd for pipex. 
 * 
 * @param argv Arguments received by pipex.
 * @retval -1 on failure.
 * @retval fd on success.
 */
int	get_output_fd(char **argv)
{
	int		fd;
	int		flag;
	char	*outfile;

	if (my_strcmp(argv[1], "here_doc") == 0)
		flag = O_APPEND;
	else
		flag = O_TRUNC;
	while (*argv)
		argv++;
	outfile = *(argv - 1);
	if (access(outfile, W_OK) == 0 || errno == ENOENT)
		fd = open(outfile, O_CREAT | O_WRONLY | flag, 0664);
	else if (errno == EACCES)
	{
		fd = open("/dev/null", O_WRONLY | flag, 0664);
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(outfile, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else
		return (-1);
	if (fd == -1)
		return (-1);
	return (fd);
}

// int	main(int argc, char **argv)
// {
// 	int	fd;

// 	fd = get_output_fd(argv);
// 	if (fd == -1)
// 		printf("error\n");
// 	else
// 		printf("success\n");
// 	close(fd);
// 	return (0);
// 	(void) argc;/////////////////////////////////////////////////////////////////
// }
