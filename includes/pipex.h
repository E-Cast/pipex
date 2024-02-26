/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:44:46 by ecast             #+#    #+#             */
/*   Updated: 2024/02/26 13:25:48 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include "errno.h"
# include <stdbool.h>

# include <stdio.h> //

typedef struct s_cmd
{
	char			*path;
	char			**args;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipex
{
	int		input_file;
	int		output_file;
	int		first_cmd;
	int		last_cmd;
	int		cmd_count;
	t_cmd	*cmd_list;
	char	**envp;
}	t_pipex;

void	open_heredoc(t_pipex *pipex, char *limiter);
void	open_infile(t_pipex *pipex, char *infile);
void	open_outfile(t_pipex *pipex, char *outfile, int flag);

#endif