/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:30:52 by ecast             #+#    #+#             */
/*   Updated: 2024/02/19 03:13:30 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Handle \, special chars, ' and "
' vs "
send the strings without '' and ""*/

int	skip_quotes(int index, char *arg_str)
{
	char	quote;


	quote = arg_str[index++];
	while (arg_str[index] && arg_str[index] != quote)
		index++;
	index++;
	return (index);
}

char	**fill_array(char **args, char *arg_str)
{
	int		start;
	int		index;
	int		arr_index;

	start = 0;
	index = 0;
	arr_index = 1;
	while (arg_str[index])
	{
		if (arg_str[index] == '\'' || arg_str[index] == '\"')
			index = skip_quotes(index, arg_str);
		if (arg_str[index] == ' ' || arg_str[index] == '\0')
		{
			args[arr_index++] = ft_substr(arg_str, start, index - start);
			if (args[arr_index - 1] == NULL)
				return (my_freearr((void **)args, arr_index));
			start = index + 1;
		}
		index++;
	}
	args[0] = ft_strjoin("/bin/", args[1]);
	if (args[0] == NULL)
		my_freearr((void **)args, arr_index);
	return (args);
}

char	**alloc_array(char *arg_str)
{
	int		index;
	int		arr_size;

	index = 0;
	arr_size = 2;
	while (arg_str[index])
	{
		if (arg_str[index] == ' ')
			arr_size++;
		if (arg_str[index] == '\'' || arg_str[index] == '\"')
			index = skip_quotes(index, arg_str);
		index++;
	}
	return (ft_calloc(arr_size + 1, sizeof(char *)));
}

// "grep 'hello world'" == 3 "grep" "hello world"
// "grep hello 'world '$" == 4 "grep" "hello" "world $"
// "grep'hello world'" == 2 "grephello world"

// "grep hello world'" or "grep 'hello world" (Do i even have to deal with them or will grep do it for me?)
// "grep 'hello \'world'"
char	**split_argstr(char *argstr)
{
	char	**args;

	args = alloc_array(argstr);
	if (args == NULL)
	{
		perror("pipex");
		return (NULL);
	}
	args = fill_array(args, argstr);
	if (args == NULL)
	{
		perror("pipex");
		return (NULL);
	}
	return (args);
}
