/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:44:46 by ecast             #+#    #+#             */
/*   Updated: 2024/03/17 22:15:52 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_command_arrays
{
	int		*inputs;
	int		*outputs;
	char	*paths;
	char	***args;
	pid_t	*pid;
}	t_cmds;

typedef struct s_arrays
{
	int		*inputs;
	int		*outputs;
	char	**paths;
	char	***args;
	pid_t	*pids;
}	t_arr;

//args.c

void	*free_args(char **args);
char	**alloc_args(char *str);
char	*extract_arg(char *str, int length);
void	*fill_args(char **args, char *str);
char	**get_args(char *argstr);

//arr.c

void	free_arr(t_arr arr, int cmd_count);
int		init_arr(t_arr *arr, char **argv, char **envp);

//count.c

int		get_first_cmd(char **argv);
int		get_cmd_count(char **argv);

//fd_arr.c

void	free_fd_arr(t_arr arr);
int		get_fd_arr(t_arr *arr, char **argv);

//infile.c

int		open_heredoc(char *delimiter);
int		get_input_fd(char **argv);

//outfile.c

int		get_output_fd(char **argv);

//path.c

char	**envp_to_paths(char **envp);
char	*free_paths(char **paths, char *retval);
char	*get_path(char *cmd, char **envp);

#endif