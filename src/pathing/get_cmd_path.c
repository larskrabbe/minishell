/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:20:35 by bogunlan          #+#    #+#             */
/*   Updated: 2022/12/31 14:42:25 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	free_path_helpers(char *tmp_path, char *join, char *new_path)
{
		free(tmp_path);
		free(join);
		free(new_path);
}

char	**get_all_paths(t_env **env_lst, char *cmd)
{
	char	**split_paths;
	char	*paths;
	char	*tmp_path;
	char	*join;
	char	*new_path;
	int		i;

	paths = ft_getenv(*env_lst, "PATH");
	if (!paths)
		return (NULL);
	split_paths = ft_split(paths, ':');
	if (!split_paths)
		return (NULL);
	i = -1;
	while (split_paths[++i])
	{
		tmp_path = ft_strdup(split_paths[i]);
		join = ft_strjoin(tmp_path, "/");
		new_path = ft_strjoin(join, cmd);
		free(split_paths[i]);
		split_paths[i] = ft_strdup(new_path);
		free_path_helpers(tmp_path, join, new_path);
	}
	return (split_paths);
}

char	*get_working_path(char **paths)
{
	int		i;
	char	*path_to_cmd;

	i = 0;
	path_to_cmd = NULL;
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
		{
			path_to_cmd = ft_strdup(paths[i]);
			break ;
		}
		i++;
	}
	return (path_to_cmd);
}

char	*get_cmd_path(t_env **env_lst, char *cmd)
{
	char	**paths;
	char	*path_to_cmd;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (!env_lst || !cmd)
		return (NULL);
	paths = get_all_paths(env_lst, cmd);
	if (paths == NULL)
		return (NULL);
	path_to_cmd = get_working_path(paths);
	// printf("path to command: %s\n", path_to_cmd);
	ft_free(paths);
	return (path_to_cmd);
}
