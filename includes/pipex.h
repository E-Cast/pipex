/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:44:46 by ecast             #+#    #+#             */
/*   Updated: 2024/02/28 23:05:48 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h> //

typedef struct s_cmd
{
	char	*path;
	char	**args;
	pid_t	pid;
}	t_cmd;

typedef struct s_pipex
{
	int		input_file;
	int		output_file;
	int		pipes[2][2];
	int		first_cmd;
	int		last_cmd;
	t_cmd	**cmd_arr;
	char	**envp;
}	t_pipex;

/*Input and output files.*/

void	open_heredoc(t_pipex *pipex, char *limiter);
void	open_infile(t_pipex *pipex, char *infile);
void	open_outfile(t_pipex *pipex, char *outfile, int flag);
void	open_fds(t_pipex *pipex, int argc, char **argv);

/*Cmd struct.*/

t_cmd	*make_cmd(char *argstr);
void	make_cmd_array(t_pipex *pipex, char **argv);

#endif