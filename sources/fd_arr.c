/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_arr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:18:41 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/17 20:53:59 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Get the index of the first valid command in argv.
 * 
 * @param argv Arguments received by pipex.
 * @retval Index of the first valid command.
 */
int	get_first_cmd(char **argv)
{
	if (my_strcmp(argv[1], "here_doc") == 0)
		return (3);
	else if (access(argv[1], R_OK) == 0)
		return (2);
	else
		return (3);
}

/**
 * @brief Get the number of valid commands.
 * 
 * @param argv Arguments received by pipex.
 * @retval Number of valid commands.
 */
int	get_cmd_count(char **argv)
{
	int	first_cmd;
	int	index;

	first_cmd = get_first_cmd(argv);
	index = first_cmd;
	while (argv[index + 1] != NULL)
		index++;
	if (access(argv[index], W_OK) == 0 || errno == ENOENT)
		return ((index - first_cmd));
	else
		return ((index - first_cmd) - 1);
}

/**
 * @brief Emulates bash's here document by using get_next_line on STDIN.
 * 
 * @param delimiter The delimiter for here_doc.
 * @retval -1 on failure.
 * @retval fd on success.
 */
int	open_heredoc(char *delimiter)
{
	int		heredoc_pipe[2];
	char	*input;

	if (pipe(heredoc_pipe) == -1)
		return (-1);
	ft_putstr_fd("> ", STDOUT_FILENO);
	input = get_next_line(STDIN_FILENO);
	while (input != NULL)
	{
		if (ft_strncmp(input, delimiter, ft_strlen(input) - 1) == 0)
			break ;
		ft_putstr_fd(input, heredoc_pipe[1]);
		my_safefree(input);
		ft_putstr_fd("> ", STDOUT_FILENO);
		input = get_next_line(STDIN_FILENO);
	}
	my_safefree(input);
	close(heredoc_pipe[1]);
	return (heredoc_pipe[0]);
}

/**
 * @brief Opens the input fd for pipex. 
 * Either with open for infile, or get_next_line for here_doc.
 * 
 * @param argv Arguments received by pipex.
 * @retval -1 on failure.
 * @retval fd on success.
 */
int	get_input_fd(char **argv)
{
	int		fd;
	char	*infile;

	if (my_strcmp(argv[1], "here_doc") == 0)
		return (open_heredoc(argv[2]));
	else
		infile = argv[1];
	if (access(infile, R_OK) == 0)
		fd = open(infile, O_RDONLY);
	else if (errno == ENOENT || errno == EACCES)
	{
		fd = open("/dev/null", O_RDONLY);
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(infile, STDERR_FILENO);
		if (errno == ENOENT)
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		if (errno == EACCES)
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else
		return (-1);
	if (fd == -1)
		return (-1);
	return (fd);
}

/**
 * @brief Opens the output fd for pipex. 
 * 
 * @param argv Arguments received by pipex.
 * @retval -1 on failure.
 * @retval fd on success.
 */
int	get_output_fd(char **argv)
{
	int		fd;
	int		flag;
	char	*outfile;

	if (my_strcmp(argv[1], "here_doc") == 0)
		flag = O_APPEND;
	else
		flag = O_TRUNC;
	while (*argv)
		argv++;
	outfile = *(argv - 1);
	if (access(outfile, W_OK) == 0 || errno == ENOENT)
		fd = open(outfile, O_CREAT | O_WRONLY | flag, 0664);
	else if (errno == EACCES)
	{
		fd = open("/dev/null", O_WRONLY | flag, 0664);
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(outfile, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else
		return (-1);
	if (fd == -1)
		return (-1);
	return (fd);
}

///////////////////////////////////////////////////////////////////////////////

void	free_fd_arr(t_arr arr)
{
	int	index;

	index = 0;
	while (arr.inputs && arr.inputs[index] != 0)
		close(arr.inputs[index++]);
	arr.inputs = my_safefree(arr.inputs);
	index = 0;
	while (arr.outputs && arr.outputs[index] != 0)
		close(arr.outputs[index++]);
	arr.outputs = my_safefree(arr.outputs);
}

int	get_fd_arr(t_arr *arr, char **argv)
{
	int		cmd_count;
	int		index;
	int		pipe_fd[2];

	cmd_count = get_cmd_count(argv);
	arr->inputs = ft_calloc(cmd_count + 1, sizeof(int));
	arr->outputs = ft_calloc(cmd_count + 1, sizeof(int));
	if (arr->inputs == NULL || arr->outputs == NULL)
		return (EXIT_FAILURE);
	index = 0;
	arr->inputs[0] = get_input_fd(argv);
	if (arr->inputs[0] == -1)
		return (EXIT_FAILURE);
	while (index + 1 < cmd_count)
	{
		if (pipe(pipe_fd) == -1)
			return (EXIT_FAILURE);
		arr->inputs[index + 1] = pipe_fd[0];
		arr->outputs[index] = pipe_fd[1];
		index++;
	}
	arr->outputs[cmd_count - 1] = get_output_fd(argv);
	if (arr->outputs[cmd_count - 1] == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_arr	arr;
	int		index;

	if (get_fd_arr(&arr, argv) == EXIT_FAILURE)
	{
		printf("error\n");
		free_fd_arr(arr);
		return (EXIT_FAILURE);
	}
	index = 0;
	while (arr.inputs[index])
	{
		printf("index:%i\ninput:%i\noutput:%i\n\n",
			index, arr.inputs[index], arr.outputs[index]);
		index++;
	}
	free_fd_arr(arr);
	return (EXIT_SUCCESS);
	(void) argc;//
}
