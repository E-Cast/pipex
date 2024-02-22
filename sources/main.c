/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:45:15 by ecast             #+#    #+#             */
/*   Updated: 2024/02/22 03:16:20 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//./pipex here_doc eof cmd1 cmd2 outfile 5
//./pipex infile cmd1 cmd2 outfile 6
void	init(t_pipex *pipex, int argc, char **argv, char **envp)
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
	pipex->args = ft_calloc(pipex->cmd_count + 1, sizeof(char *));
	if (pipex->path == NULL || pipex->args == NULL)
		return ;//terminate
	// get paths and args for every cmd
	// put them into the paths and args array
	pipex->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	if (pipex == NULL)
		return (1);//terminate
	init(pipex, argc, argv, envp);

	char	*read;
	read = get_next_line(pipex->input_file);
	while (read != NULL)
	{
		printf("%s", read);
		ft_putstr_fd(read, pipex->output_file);
		read = get_next_line(pipex->input_file);
	}
}
