/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:01:13 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/17 18:32:21 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	count_pipes(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (*args)
	{
		i++;
		args++;
	}
	return (i);
}

int	create_pipes(int *fd, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(fd + i * 2) < 0)
		{
			printf("Pipe not created\n");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int ft_pipe(char **args, t_env **env_lst)
{
	int		status;
	int		i;
	int		j;
	int		*fd;
	int		num_pipes;
	int		pid;
	char	**split;
	char	*path;
	char	**env;


	if (!env_lst)
		return (error_null_ptr);
	num_pipes = count_pipes(args);
	if (num_pipes > 1)
		num_pipes -= 1;
	else
		num_pipes = 0;
	if (num_pipes < 1)
		return (error_null_ptr);
	fd = (int *) malloc(2 * num_pipes * sizeof(int) + 1);
	if (!fd)
		return (error_allocation);
	if (create_pipes(fd, num_pipes) == 0)
		return (error_null_ptr);
	j = 0;
	while (args && *args)
	{
		pid = fork();
		if (pid < 0)
		{
			printf("Error: child process fork\n");
			return (error_null_ptr);
		}
		if (pid == 0)
		{
			//if not last command
			if (args + 1)
			{
				if (dup2(fd[j + 1], STDOUT_FILENO) < 0)
				{
					printf("Error, 1st dup2\n");
					return (error_null_ptr);
				}
			}
			//if not first command
			if (j != 0)
			{
				if (dup2(fd[j - 2], STDIN_FILENO) < 0)
				{
					printf("Error, 2nd dup2\n");
					return (error_null_ptr);
				}
			}
			i = 0;
			while (i < 2 * num_pipes)
			{
				close(fd[i]);
				i++;
			}
			printf("Arg->%s\n", *args);
			split = ft_split(*args, ' ');
			path = get_cmd_path(env_lst, split[0]);
			env = env_as_string(env_lst);
			if (!path || !split)
				return (error_allocation);
			printf("****%s****\ncmd:%s\n",path, *args);
			if (execve(path, split, env) < 0)
			{
				printf("Error executing\n");
				return (error_syntax);
			}
			ft_free(split);
			split = NULL;
		}
		args++;
		j += 2;
	}
	i = 0;
	while (i < (2 * num_pipes))
	{
		close(fd[i]);
		i++;
	}
	i = 0;
	while (i < num_pipes)
	{
		waitpid(pid, &status, 0);
		i++;
	}
	free(fd);
	return (0);
}
