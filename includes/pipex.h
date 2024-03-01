/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:44:46 by ecast             #+#    #+#             */
/*   Updated: 2024/03/01 07:59:14 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		input_file;
	int		output_file;
	int		pipes[2][2];

	int		first_cmd;
	int		last_cmd;
	char	**envp;

	char	**path;
	char	***args;
	pid_t	*pid;

	int		exit_code;
}	t_pipex;

/*File descriptors.*/

void	put_heredoc(t_pipex *pipex);
void	open_heredoc(t_pipex *pipex, char *limiter);
void	open_infile(t_pipex *pipex, char *infile);
void	open_outfile(t_pipex *pipex, char *outfile, int flag);
void	open_fds(t_pipex *pipex, int argc, char **argv);

/*Cmd struct.*/

void	make_cmd(t_pipex *pipex, int index, char *argstr);
void	make_cmd_arrays(t_pipex *pipex, char **argv);

/*Execution of commands.*/

int		get_input(t_pipex *pipex, int index);
int		get_output(t_pipex *pipex, int index);
void	exec_cmd(t_pipex *pipex, int index, int input, int output);
void	exec_pipex(t_pipex *pipex);

/*Utility and cleanup.*/

void	close_all(t_pipex *pipex);
void	wait_all(t_pipex *pipex);
void	free_all(t_pipex *pipex);
void	terminate(t_pipex *pipex, int code);

#endif