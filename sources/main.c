/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:45:15 by ecast             #+#    #+#             */
/*   Updated: 2024/02/16 21:54:41 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// 0"name" 1"infile" 2"cmd" 3"cmd" 4"outfile" argc == 5
t_list	*process_args(int argc, char **argv)
{
	t_list	*args;
	int		index;

	index = 2;
	while (index > argc - 1)
	{
		args = ft_lstnew(ft_split(argv[index], ' '));
		index++;
	}
	return (&args);
}

int	main(int argc, char **argv)
{
	t_list	*args;

	if (argc < 5)
	{
		ft_putendl_fd("Error: Not enough arguments.", STDERR_FILENO); //
		return (1);
	}
	args = process_args(argc, argv);
	(void) args;
}
