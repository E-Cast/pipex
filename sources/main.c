/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:45:15 by ecast             #+#    #+#             */
/*   Updated: 2024/02/17 18:06:22 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h>
// 0"name" 1"infile" 2"cmd" 3"cmd" 4"outfile" argc == 5
char	**prep_arg(char *arg_str)
{
	char	**split_string;
	char	**args;
	int		index;

	split_string = ft_split(arg_str, ' ');
	index = 0;
	while (split_string[index] != NULL)
		index++;
	args = ft_calloc(index + 2, sizeof(char *));
	args[0] = ft_strjoin("/bin/", split_string[0]);
	index = 0;
	while (split_string[index] != NULL)
	{
		args[index + 1] = split_string[index];
		index++;
	}
	my_safefree(split_string);
	return (args);
}

int	main(int argc, char **argv)
{
	char	**args;
	int		index;

	(void) argc;
	args = prep_arg(argv[2]);
	index = 0;
	while (args[index] != NULL)
	{
		printf("%s\n", args[index++]);
	}
}
