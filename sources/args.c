/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:30:52 by ecast             #+#    #+#             */
/*   Updated: 2024/02/18 22:40:11 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
handle inputs for 
Handle \, !, ' and "
' vs "
Handle only one ' or " (dquote)
"grep 'hello world'"
*/

char	**alloc_array(char *argstr)
{
	int	index;
	int	arr_size;

	index = 0;
	arr_size = 1;
	while (argstr[index])
	{
		if (argstr[index] == ' ')
			arr_size++;
		if (argstr[index] == '\'')
		{
			index++;
			while (argstr[index] && argstr[index] != '\'')
				index++;
		}
		index++;
	}
	printf("%i\n", arr_size);
	return (ft_calloc(arr_size + 1, sizeof(char *)));
}

// "grep 'hello world'" == 2 "grep" "hello world"
// "grep hello 'world '$" == 3 "grep" "hello" "world $"
// "grep'hello world'" == 1 "grephello world"

// "grep hello world'" or "grep 'hello world" (Do i even have to deal with them or will grep do it for me?)
// "grep 'hello \'world'"
char	**split_argstr(char *argstr)
{
	char	**args;

	args = alloc_array(argstr);
	// args[0] = ft_strjoin("/bin/", args[1]);
	// if (args[0] == NULL)
	//	free_array(&array[1]);
	return (args);
}
