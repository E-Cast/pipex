/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 00:09:03 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/18 21:07:51 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Frees the args array.
 * 
 * @param args The array to be freed.
 * @retval NULL
 */
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

/**
 * @brief Allocates the args array.
 * 
 * @param s The string to be split into args.
 * @retval NULL on failure.
 * @retval The args array on success.
 */
char	**alloc_args(char *s)
{
	int		count;
	char	quote;
	int		i;

	count = 1;
	quote = 0;
	i = 0;
	while (s[i] != 0)
	{
		if (quote == 0 && s[i] == ' ' && s[i + 1] != ' ' && s[i + 1] != '\0')
			count++;
		else if (quote == 0 && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (quote != 0 && (s[i] == '\'' || s[i] == '\"'))
			quote = 0;
		else if ((quote == '\"' || quote == 0) && s[i] == '\\')
			i++;
		i++;
	}
	return (ft_calloc(count + 1, sizeof(char *)));
}

/**
 * @brief Extracts an argument from the str.
 * 
 * @param str The string to extract from.
 * @param length How much to extract from the string.
 * @retval NULL on failure.
 * @retval The argument on success.
 */
char	*extract_arg(char *str, int length)
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
		if (quote == 0 && str[str_inx] == ' ')
			quote = 0;
		else if (quote == 0 && (str[str_inx] == '\'' || str[str_inx] == '\"'))
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

/**
 * @brief Splits the string into the array.
 * 
 * @param args The args array.
 * @param s The string to be split.
 * @retval NULL on failure.
 * @retval The args array on success.
 */
void	*fill_args(char **args, char *s)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] != 0)
	{
		if (quote == 0 && s[i] == ' ' && s[i + 1] != ' ' && s[i + 1] != '\0')
		{
			*args++ = extract_arg(s, i);
			if (*(args - 1) == NULL)
				return (NULL);
			s += i + 1;
			i = -1;
		}
		else if (quote == 0 && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (quote != 0 && (s[i] == '\'' || s[i] == '\"'))
			quote = 0;
		i++;
	}
	*args = extract_arg(s, i);
	return (args);
}

/**
 * @brief Allocates the args array and splits argstr into it.
 * 
 * @param argstr The string to be split.
 * @retval NULL on failure.
 * @retval The args array on success.
 */
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
