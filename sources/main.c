/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:45:15 by ecast             #+#    #+#             */
/*   Updated: 2024/03/05 07:55:17 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 5)
	{
		ft_putendl_fd("pipex: too few arguments", STDERR_FILENO);
		return (1);
	}
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (pipex == NULL)
	{
		perror("pipex: ft_calloc");
		return (1);
	}
	open_fds(pipex, argc, argv);
	make_cmd_arrays(pipex, argv);
	pipex->envp = envp;
	terminate(pipex, exec_pipex(pipex), 0, NULL);
}
