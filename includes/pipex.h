/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:44:46 by ecast             #+#    #+#             */
/*   Updated: 2024/02/22 22:05:48 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include "errno.h"
# include <stdbool.h>

# include <stdio.h> //

typedef struct s_pipex
{
	int		input_file;
	int		output_file;
	int		cmd_count;
	char	**path;
	char	***args;
	char	**envp;
}	t_pipex;

void	open_heredoc(t_pipex *pipex, char *limiter);
void	open_infile(t_pipex *pipex, char *infile);
void	open_outfile(t_pipex *pipex, char *outfile, int flag);

// char	**split_argstr(char *argstr);

#endif