/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:45:15 by ecast             #+#    #+#             */
/*   Updated: 2024/02/26 15:38:23 by ecast            ###   ########.fr       */
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

void	make_cmd(t_pipex *pipex, char *argstr, char **envp)
{
	t_cmd	*cmd_node;

	cmd_node = ft_calloc(1, sizeof(t_cmd));
	if (cmd_node == NULL)
		return ;//terminate failure error
	cmd_node->args = ft_split(argstr, ' ');
	if (cmd_node->args == NULL)
		return ;//terminate failure error
	cmd_node->path = ft_strjoin("/usr/bin/", cmd_node->args[0]);
	if (cmd_node->path == NULL)
		return ;//terminate failure error
	cmd_lst_add(&pipex->cmd_list, cmd_node);//to change
	cmd_node->envp = envp;
}

void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->last_cmd = argc - 2;
	if (my_strcmp(argv[1], "here_doc") == 0)
	{
		pipex->first_cmd = 3;
		open_heredoc(pipex, argv[2]);
		open_outfile(pipex, argv[argc - 1], O_APPEND);
		pipex->cmd_count = argc - 4;
	}
	else
	{
		pipex->first_cmd = 2;
		open_infile(pipex, argv[1]);
		open_outfile(pipex, argv[argc - 1], O_TRUNC);
		pipex->cmd_count = argc - 3;
	}
	if (pipex->last_cmd < pipex->first_cmd)
		printf("terminate\n");// return ;//terminate failure no error
	while (pipex->first_cmd <= pipex->last_cmd)
		make_cmd(pipex, argv[pipex->first_cmd++], envp);
}

// void	exec_pipex()
// {
// 	// (void) pipex;
// }

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 4)
		return (1);//terminate failure error
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (pipex == NULL)
		return (1);//terminate failure error
	init_pipex(pipex, argc, argv, envp);
	// exec_pipex(pipex);

	// char	*read;
	// read = get_next_line(pipex->input_file);
	// while (read != NULL)
	// {
	// 	ft_putstr_fd(read, pipex->output_file);
	// 	read = get_next_line(pipex->input_file);
	// }
	// t_cmd	*cmd = pipex->cmd_list;
	// // printf("%s$\n%s$\n%s$\n%s$\n", cmd->path, cmd->args[0], cmd->args[1], cmd->args[2]);
	// // dup2(pipex->input_file, STDIN_FILENO);
	// // close(pipex->input_file);
	// dup2(open("/dev/null", O_RDONLY), STDIN_FILENO);
	// // close(STDIN_FILENO);
	// dup2(pipex->output_file, STDOUT_FILENO);
	// close(pipex->output_file);
	// execve(cmd->path, cmd->args, pipex->envp);
}
