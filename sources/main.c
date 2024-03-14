/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:28:18 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/14 11:55:03 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	utils.input_file = open_input(argv, &utils.first_cmd);
	printf("%i\n%i\n", utils.input_file, utils.first_cmd);
	(void) argc;
	(void) envp;
}
