/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:17:47 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/14 17:49:53 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_env_path(char **envp)
{
	int		index;
	char	**env_path;

	index = 0;
	env_path = NULL;
	while (envp[index])
	{
		if (ft_strncmp("PATH=", envp[index], 5) == 0)
			env_path = ft_split(&envp[index][5], ':');
		index++;
	}
	return (env_path);
}

char	*get_path(t_utils *utils, char *cmd)
{
	char	*path;
	int		index;

	index = 0;
	while (utils->env_path[index])
	{
		path = my_jointhree(utils->env_path[index], "/", cmd);
		if (path == NULL)
			terminate(utils, NULL, EXIT_FAILURE);
		if (access(path, X_OK) == 0)
			return (path);
		index++;
	}
	return (NULL);
}
