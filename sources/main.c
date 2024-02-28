/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:45:15 by ecast             #+#    #+#             */
/*   Updated: 2024/02/28 17:08:35 by ecast            ###   ########.fr       */
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

void	exec_pipex(t_pipex *pipex)
{
	(void) pipex;
	// t_cmd	*command;

	// command = pipex->cmd_lst;
	// while (command)
	// {
	// 	printf("%i\n", command->index);
	// 	printf("%s\n%s\n", command->args[0], command->path);
	// 	command = command->next;
	// }
	/*
	get the pipes
	while commands to be executed
		fork
		find the right fds
		call exec_cmd with the t_cmd
		dup2 on fds
		execve
		get next t_cmd
	while pids to wait out
		get pid from t_cmd
		wait pid
		get next t_cmd
	*/
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 4)
		exit(1);//terminate
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (pipex == NULL)
		exit(1);//terminate
	open_fds(pipex, argc, argv);
	make_cmd_array(pipex, argv);
	pipex->envp = envp;

	exec_pipex(pipex);

	// char	*read;
	// read = get_next_line(pipex->input_file);
	// while (read != NULL)
	// {
	// 	ft_putstr_fd(read, pipex->output_file);
	// 	read = get_next_line(pipex->input_file);
	// }
	// t_cmd	*cmd = pipex->cmd_lst;
	// // printf("%s$\n%s$\n%s$\n%s$\n", cmd->path, cmd->args[0], cmd->args[1], cmd->args[2]);
	// // dup2(pipex->input_file, STDIN_FILENO);
	// // close(pipex->input_file);
	// dup2(open("/dev/null", O_RDONLY), STDIN_FILENO);
	// // close(STDIN_FILENO);
	// dup2(pipex->output_file, STDOUT_FILENO);
	// close(pipex->output_file);
	// execve(cmd->path, cmd->args, pipex->envp);
}
