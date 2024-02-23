/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecast <ecast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:45:15 by ecast             #+#    #+#             */
/*   Updated: 2024/02/23 03:15:09 by ecast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//./pipex "grep 'Hello \' World"
//./pipex 'grep "Hello \" World"'

/*
Get nbr of args to allocate the args array
while argstr
Get next block
interpret it
put the interpreted block in the array
*/

void	alloc_args_array(char ***array, char *argstr)
{
	int	index;
	int	arg_count;
	int	status;

	index = 0;
	arg_count = 1;
	status = 0;
	while (argstr[index])
	{
		if (status == 0 && (argstr[index] == '\'' || argstr[index] == '\"'))
			status = argstr[index];
		else if ((status == 0 || status == '\"') && argstr[index] == '\\')
			index++;
		else if (status != 0 && argstr[index] == status)
			status = 0;
		else if (status == 0 && argstr[index] == ' ')
			arg_count++;
		index++;
	}
	*array = ft_calloc(arg_count + 1, sizeof(char *));
	*array[0] = ft_strdup("Hello Test");
	if (*array == NULL)
		return ;//terminate
}

void	parse_cmds(t_pipex *pipex, int argc, char **argv)
{
	int	index;

	index = argc - (pipex->cmd_count + 1);
	printf("%i\n%i\n", index, argc);
	while (index < argc - 1)
	{
		alloc_args_array(&pipex->args[index - (argc - 3)], argv[index]);
		// printf("%s\n", pipex->args[index - (argc - 3)][0]);
		index++;
	}
}

//./pipex infile 'grep "Hello \" World"'(2) "grep 'Hello \' World"(3) outfile 6
//./pipex here_doc EOF cmd1 cmd2 outfile 5
void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
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
	pipex->args = ft_calloc(pipex->cmd_count + 1, sizeof(char **));
	if (pipex->path == NULL || pipex->args == NULL)
		return ;//terminate
	parse_cmds(pipex, argc, argv);
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
	init_pipex(pipex, argc, argv, envp);

	//////////////////////////////////////////////////////////
	char	*read;
	read = get_next_line(pipex->input_file);
	while (read != NULL)
	{
		printf("%s", read);
		ft_putstr_fd(read, pipex->output_file);
		read = get_next_line(pipex->input_file);
	}
}
