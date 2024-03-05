/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:30:52 by ecast             #+#    #+#             */
/*   Updated: 2024/03/05 08:32:55 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*make_segment(t_pipex *pipex, char *str, int start, int end)
{
	char	*segment;
	int		str_inx;
	int		seg_inx;
	char	quote;

	segment = ft_calloc((end - start) + 1, sizeof(char));
	if (segment == NULL)
		terminate(pipex, EXIT_FAILURE, errno, "pipex: ft_calloc");
	str_inx = start;
	seg_inx = 0;
	quote = 0;
	while (str_inx < end)
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
	if (segment == NULL)
		terminate(pipex, EXIT_FAILURE, errno, "pipex: my_strrealloc");
	return (segment);
}

char	**segment_str(t_pipex *pipex, char **array, char *str)
{
	char	quote;
	int		start;
	int		str_inx;

	quote = 0;
	start = 0;
	str_inx = 0;
	while (str[str_inx] != 0)
	{
		if (str[str_inx] == ' ' && quote == 0)
		{
			*array = make_segment(pipex, str, start, str_inx);
			array++;
			start = str_inx + 1;
		}
		else if (quote == 0 && (str[str_inx] == '\'' || str[str_inx] == '\"'))
			quote = str[str_inx];
		else if (quote != 0 && (str[str_inx] == '\'' || str[str_inx] == '\"'))
			quote = 0;
		str_inx++;
	}
	if (start != str_inx)
		*array = make_segment(pipex, str, start, str_inx);
	return (array);
}

int	count_segments(char *str)
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
	return (count);
}

void	make_cmd(t_pipex *pipex, int index, char *argstr)
{
	pipex->args[index] = ft_calloc(count_segments(argstr) + 1, sizeof(char *));
	if (pipex->args[index] == NULL)
		terminate(pipex, EXIT_FAILURE, errno, "pipex: ft_calloc");
	segment_str(pipex, pipex->args[index], argstr);
	pipex->path[index] = ft_strjoin("/usr/bin/", pipex->args[index][0]);
	if (pipex->path[index] == NULL)
		terminate(pipex, EXIT_FAILURE, errno, "pipex: ft_strjoin");
}

void	make_cmd_arrays(t_pipex *pipex, char **argv)
{
	int	cmd_count;
	int	argv_index;
	int	arr_index;

	cmd_count = pipex->last_cmd - (pipex->first_cmd - 1);
	pipex->args = ft_calloc(cmd_count + 1, sizeof(char **));
	if (pipex->args == NULL)
		terminate(pipex, EXIT_FAILURE, errno, "pipex: ft_calloc");
	pipex->path = ft_calloc(cmd_count + 1, sizeof(char *));
	if (pipex->path == NULL)
		terminate(pipex, EXIT_FAILURE, errno, "pipex: ft_calloc");
	pipex->pid = ft_calloc(cmd_count + 1, sizeof(char *));
	if (pipex->pid == NULL)
		terminate(pipex, EXIT_FAILURE, errno, "pipex: ft_calloc");
	argv_index = pipex->first_cmd;
	arr_index = 0;
	while (argv_index <= pipex->last_cmd)
	{
		make_cmd(pipex, arr_index, argv[argv_index]);
		arr_index++;
		argv_index++;
	}
}
