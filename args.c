/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 00:09:03 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/18 21:07:35 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(int argc, char **argv)
{
	int	index;

	index = 1;
	while (argv[index])
		ft_putendl_fd(argv[index++], STDERR_FILENO);
	(void) argc;
}
