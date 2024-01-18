/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 06:34:27 by ecastong          #+#    #+#             */
/*   Updated: 2024/01/18 07:21:04 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf.h"


// int	check_args()
// {
// 	check if it has an heredoc argument
// }

// void	bonus()
// {
// 	run pipex as bonus
// }

// void	pipex_init(int argc, char **argv)
// {
// 	// initialize infile and outfile while checking their validity
// }

// int	main(int argc, char **argv)
// {
// 	pipex_init(argc, argv);
// 	// if (check_args() == bonus)
// 	// 	here_doc();
// 	// else
// 	// 	pipex();
// }

/*
Files tests:
	cmd:
		< infile grep test | tee thirdfile | wc -l > outfile
	infile:
		valid: Run commands with it as first input.
		nonexistant: Run commands with no input. Error: "bash: filename: No such file or directory"
		permissions missing: Run commands with no input. Error: "bash: filename: Permission denied"
		not a text file: Run commands with no input.
	outfile:
		valid: Send final output to it.
		nonexistant: Create it and send final output to it.
		permissions missing: Don't run the cmds. Error "bash: filename: Permission denied"
		not a text file: Run commands and output them to it, turning it into a text file.
Cmd tests:
	invalid cmd:
		< infile grep test | tee thirdfile | invalidcmd | tee fourthfile | wc -l > outfile
	behavior:
		Still runs every commands in the chain no matter where the cmd is in it.
		Error "invalidcmd: command not found"
		or
		Command 'invalidcmd' not found, did you mean:
			command 'example1' from deb source
			command 'example2' from deb source
			command 'example3' from deb source
			command 'example4' from deb source
	cmd failed:
		< infile grep test | tee thirdfile | grep test | tee fourthfile | wc -l > outfile
	behavior:
		when called with either thirdfile or fourthile at 0 permissions, it fails to run that specific command but continues the chain.
		Error "tee: filename: Permission denied"
*/