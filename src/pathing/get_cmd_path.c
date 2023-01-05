/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:20:35 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/05 16:19:48 by bogunlan         ###   ########.fr       */
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
	t_path	path;
	char	**split_paths;
	int		i;

	path.paths = ft_getenv(*env_lst, "PATH");
	if (!path.paths)
		return (NULL);
	split_paths = ft_split(path.paths, ':');
	if (!split_paths)
		return (NULL);
	i = -1;
	while (split_paths[++i])
	{
		path.tmp_path = ft_strdup(split_paths[i]);
		path.join_fwd_slash = ft_strjoin(path.tmp_path, "/");
		path.new_path = ft_strjoin(path.join_fwd_slash, cmd);
		free(split_paths[i]);
		split_paths[i] = ft_strdup(path.new_path);
		free_path_helpers(path.tmp_path, path.join_fwd_slash, path.new_path);
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

int	cmd_has_current_path(char *cmd)
{
	int	i;
	char **split = ft_split(cmd, '/');

	i = 0;
	while (split[i])
		i++;
	ft_free(split);
	if (i <= 1)
		return (FALSE);
	return (TRUE);
}

char	*get_cmd_path(t_env **env_lst, char *cmd)
{
	char	**paths;
	char	*path_to_cmd;

	if (access(cmd, X_OK) == 0)
	{
		if (!cmd_has_current_path(cmd))
			return (NULL);
		return (cmd);
	}
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
