/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 00:09:03 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/16 01:25:31 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*free_args(char **args)
{
	int	index;

	index = 0;
	while (args && args[index])
	{
		args[index] = my_safefree(args[index]);
		index++;
	}
	args = my_safefree(args);
	return (NULL);
}

char	**alloc_args(char *str)
{
	int		count;
	char	quote;
	int		ix;

	count = 1;
	quote = 0;
	ix = 0;
	while (str[ix] != 0)
	{
		if (str[ix] == ' ' && quote == 0)
			count++;
		else if (quote == 0 && (str[ix] == '\'' || str[ix] == '\"'))
			quote = str[ix];
		else if (quote != 0 && (str[ix] == '\'' || str[ix] == '\"'))
			quote = 0;
		else if ((quote == '\"' || quote == 0) && str[ix] == '\\')
			ix++;
		ix++;
	}
	return (ft_calloc(count + 1, sizeof(char *)));
}

char	*make_segment(char *str, int length)
{
	char	*segment;
	int		str_inx;
	int		seg_inx;
	char	quote;

	segment = ft_calloc(length + 1, sizeof(char));
	if (segment == NULL)
		return (NULL);
	str_inx = 0;
	seg_inx = 0;
	quote = 0;
	while (str_inx < length)
	{
		if (quote == 0 && (str[str_inx] == '\'' || str[str_inx] == '\"'))
			quote = str[str_inx];
		else if (quote != 0 && (str[str_inx] == '\'' || str[str_inx] == '\"'))
			quote = 0;
		else
			segment[seg_inx++] = str[str_inx];
		str_inx++;
	}
	my_strrealloc(&segment);
	return (segment);
}

void	*fill_args(char **args, char *str)
{
	char	quote;
	int		str_inx;

	quote = 0;
	str_inx = 0;
	while (str[str_inx] != 0)
	{
		if (str[str_inx] == ' ' && quote == 0)
		{
			*args++ = make_segment(str, str_inx);
			if (*(args - 1) == NULL)
				return (NULL);
			str += str_inx + 1;
			str_inx = -1;
		}
		else if (quote == 0 && (str[str_inx] == '\'' || str[str_inx] == '\"'))
			quote = str[str_inx];
		else if (quote != 0 && (str[str_inx] == '\'' || str[str_inx] == '\"'))
			quote = 0;
		str_inx++;
	}
	*args = make_segment(str, str_inx);
	if (*args == NULL)
		return (NULL);
	return (args);
}

char	**get_args(char *argstr)
{
	char	**args;

	args = alloc_args(argstr);
	if (args == NULL)
		return (NULL);
	if (argstr[0] == '\0')
	{
		args[0] = ft_strdup("");
		if (args[0] == NULL)
			args = my_safefree(args);
		return (args);
	}
	if (fill_args(args, argstr) == NULL)
		return (free_args(args));
	return (args);
}

int	main(int argc, char **argv)
{
	char	**args;
	int		index;

	printf("%s\n", argv[1]);
	args = get_args(argv[1]);
	if (args == NULL)
		printf("Error\n");
	else
	{
		index = 0;
		while (args[index])
			printf("%s\n", args[index++]);
		args = free_args(args);
	}
	(void) argc;
}
