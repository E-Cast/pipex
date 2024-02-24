/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:45:15 by ecast             #+#    #+#             */
/*   Updated: 2024/02/24 05:20:54 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
./pipex "grep 'Hello \' World"
grep
'hello \'
world
*/
/*
./pipex 'grep "Hello \" World"'
grep
Hello " World
*/

//./pipex infile 'grep "Hello \" World"'(2) "grep 'Hello \' World"(3) outfile 6
//./pipex here_doc EOF cmd1 cmd2 outfile 5
void	parse_cmds(t_pipex *pipex, int argc, char **argv)
{
	int	argv_i;
	int	args_i;

	args_i = 0;
	argv_i = argc - (pipex->cmd_count + 1);
	while (argv_i < argc - 1)
	{
		pipex->args[args_i] = ft_split(argv[argv_i], ' ');
		if (pipex->args[args_i] == NULL)
			return ;//terminate
		pipex->path[args_i] = ft_strjoin("/usr/bin/", pipex->args[args_i][0]);
		if (pipex->path[args_i] == NULL)
			return ;//terminate
		// printf("%s\n", pipex->args[args_i][0]);
		// printf("%s\n", pipex->args[args_i][1]);
		// printf("%s\n", pipex->path[args_i]);
		args_i++;
		argv_i++;
	}
}

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (my_strcmp(argv[1], "here_doc") == 0)
	{
		open_heredoc(pipex, argv[2]);
		open_outfile(pipex, argv[argc - 1], O_APPEND);
		pipex->cmd_count = argc - 4;
	}
	else
	{
		open_infile(pipex, argv[1]);
		open_outfile(pipex, argv[argc - 1], O_TRUNC);
		pipex->cmd_count = argc - 3;
	}
	pipex->path = ft_calloc(pipex->cmd_count + 1, sizeof(char *));
	pipex->args = ft_calloc(pipex->cmd_count + 1, sizeof(char **));
	if (pipex->path == NULL || pipex->args == NULL)
		return ;//terminate
	parse_cmds(pipex, argc, argv);
	pipex->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 4)
		return (1);//terminate
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (pipex == NULL)
		return (1);//terminate
	init_pipex(pipex, argc, argv, envp);

	char	*read;
	read = get_next_line(pipex->input_file);
	while (read != NULL)
	{
		ft_putstr_fd(read, pipex->output_file);
		read = get_next_line(pipex->input_file);
	}
}
