/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:45:15 by ecast             #+#    #+#             */
/*   Updated: 2024/02/19 03:10:10 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// char	**get_args(char *arg_str)
// {
// 	char	**args;
// 	int		index;

// 	split_string = ft_split(arg_str, ' ');
// 	index = 0;
// 	while (split_string[index] != NULL)
// 		index++;
// 	args = ft_calloc(index + 2, sizeof(char *));
// 	args[0] = ft_strjoin("/bin/", split_string[0]);
// 	index = 0;
// 	while (split_string[index] != NULL)
// 	{
// 		args[index + 1] = split_string[index];
// 		index++;
// 	}
// 	my_safefree(split_string);
// 	return (args);
// }

int	main(int argc, char **argv)
{
	int	i = 0;
	(void) argc;
	(void) argv;
	// printf("%i\n", argc);
	// while (argv[i] != NULL)
	// 	printf("%s\n", argv[i++]);
	split_argstr(argv[i - 1]);
}
