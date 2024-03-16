/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:53:40 by ecastong          #+#    #+#             */
/*   Updated: 2024/03/15 23:24:17 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**envp_to_paths(char **envp)
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

char	*free_paths(char **paths, char *return_value)
{
	int	index;

	index = 0;
	while (paths[index])
		my_safefree(paths[index++]);
	paths = my_safefree(paths);
	return (return_value);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		index;

	paths = envp_to_paths(envp);
	if (paths == NULL)
		return (NULL);
	index = 0;
	while (cmd[0] && paths[index])
	{
		path = my_jointhree(paths[index], "/", cmd);
		if (path == NULL)
			return (free_paths(paths, NULL));
		else if (access(path, X_OK) == 0)
			return (free_paths(paths, path));
		path = my_safefree(path);
		index++;
	}
	return (free_paths(paths, ft_strdup("")));
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;

	printf("%s\n", argv[1]);
	path = get_path(argv[1], envp);
	if (path == NULL)
		printf("Error\n");
	else if (path[0] == '\0')
		printf("invalid command\n");
	else
		printf("%s\n", path);
	free(path);
	(void) argc;
}
