/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:44:46 by ecast             #+#    #+#             */
/*   Updated: 2024/02/21 19:33:08 by ecast            ###   ########.fr       */
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
	bool	here_doc;
	int		cmd_count;
	char	**path;
	char	***args;
	char	**envp;
}	t_pipex;

// int	

// char	**split_argstr(char *argstr);

#endif