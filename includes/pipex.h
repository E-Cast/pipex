/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:44:46 by ecast             #+#    #+#             */
/*   Updated: 2024/03/14 17:12:21 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	int		fd[2];
	char	*path;
	char	**args;
	pid_t	pid;
}	t_cmd;

typedef struct utility_variables
{
	int		input_file;
	int		output_file;
	int		first_cmd;
	int		last_cmd;
	char	**env_path;
	t_cmd	**cmd_arr;
}	t_utils;

int		open_heredoc(char *delimiter, int *first_cmd);
int		open_infile(char *infile, int *first_cmd);
int		open_input(char **argv, int *first_cmd);

int		open_outfile(char *outfile, int flag, int *last_cmd);
int		open_output(int argc, char **argv, int *last_cmd);

void	terminate(t_utils *utils, int exit_code);

char	**get_env_path(char **envp);
/*Struct used to pass all relevant data in the program 
	and ensure no leaks are created when terminating.*/
typedef struct s_pipex
{
	int		input_file;
	int		output_file;
	int		(*p_arr)[2];
	int		first_cmd;
	int		last_cmd;
	char	**envp;
	char	**path;
	char	***args;
	pid_t	*pid;
}	t_pipex;

/*File descriptors.*/

void	open_fds(t_pipex *pipex, int argc, char **argv);

/*Parsing and preparation of commands.*/

char	*make_segment(t_pipex *pipex, char *str, int start, int end);
char	**segment_str(t_pipex *pipex, char **array, char *str);
int		count_segments(char *str);
void	fill_array(t_pipex *pipex, int index, char *argstr);
void	make_arrays(t_pipex *pipex, char **argv);

/*Execution of commands.*/

int		get_input(t_pipex *pipex, int index);
int		get_output(t_pipex *pipex, int index);
void	exec_cmd(t_pipex *pipex, int index, int input, int output);
int		exec_pipex(t_pipex *pipex);

/*Utility and cleanup.*/

void	close_all(t_pipex *pipex);
int		wait_all(t_pipex *pipex);
int		free_all(t_pipex *pipex);

#endif