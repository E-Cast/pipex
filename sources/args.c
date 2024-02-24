/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:30:52 by ecast             #+#    #+#             */
/*   Updated: 2024/02/24 04:57:50 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	parse_args_array(char ***array, char *argstr)
// {
// 	int	index;
// 	int	start;
// 	int	status;

// 	index = 0;
// 	start = 0;
// 	status = 0;
// 	while (argstr[index])
// 	{
// 		if (status == 0 && (argstr[index] == '\'' || argstr[index] == '\"'))
// 		{
// 			status = argstr[index];
// 			start = index + 1;
// 		}
// 		else if ((status == 0 || status == '\"') && argstr[index] == '\\')
// 			index++;
// 		else if (status != 0 && argstr[index] == status)
// 			status = 0;
// 		else if (status == 0 && argstr[index] == ' ')

// 		index++;
// 	}
// 	if (*array == NULL)
// 		return ;//terminate
// }

// void	alloc_args_array(char ***array, char *argstr)
// {
// 	int	index;
// 	int	arg_count;
// 	int	status;

// 	index = 0;
// 	arg_count = 1;
// 	status = 0;
// 	while (argstr[index])
// 	{
// 		if (status == 0 && (argstr[index] == '\'' || argstr[index] == '\"'))
// 			status = argstr[index];
// 		else if ((status == 0 || status == '\"') && argstr[index] == '\\')
// 			index++;
// 		else if (status != 0 && argstr[index] == status)
// 			status = 0;
// 		else if (status == 0 && argstr[index] == ' ')
// 			arg_count++;
// 		index++;
// 	}
// 	*array = ft_calloc(arg_count + 1, sizeof(char *));
// 	if (*array == NULL)
// 		return ;//terminate
// }