/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:42:39 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/25 02:30:47 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*string_to_lower(char *str)
{
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	new_str = (char *) ft_calloc(ft_strlen(str) + 1 \
	, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (*str)
	{
		new_str[i] = ft_tolower(*str);
		i++;
		str++;
	}
	return (new_str);
}

int	has_upper_case(char *str)
{
	if (!str)
		return (FALSE);
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

int	find_builtin_match(char *cmd, char *builtin)
{
	if (ft_strncmp(cmd, builtin, ft_strlen(cmd)) == 0)
	{
		if (ft_strncmp(cmd, builtin, ft_strlen(builtin)) == 0)
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

int	cmd_is_builtin(char *cmd)
{
	char	*command;

	command = string_to_lower(cmd);
	if (!command)
		return (FALSE);
	if (find_builtin_match(command, "echo")
		|| find_builtin_match(command, "pwd")
		|| find_builtin_match(command, "env")
		|| (find_builtin_match(command, "cd") && !has_upper_case(cmd))
		|| (find_builtin_match(command, "export") && !has_upper_case(cmd))
		|| (find_builtin_match(command, "unset") && !has_upper_case(cmd))
		|| (find_builtin_match(command, "exit") && !has_upper_case(cmd)))
	{
		free(command);
		return (TRUE);
	}
	free(command);
	return (FALSE);
}

int	handle_builtin(char *cmd, char **args, t_env **env)
{
	char	*command;
	int		result;

	command = string_to_lower(cmd);
	result = no_error;
	if (!command)
		return (error_allocation);
	if (find_builtin_match(command, "echo"))
		result = ft_echo(args);
	if (find_builtin_match(command, "pwd"))
		result = ft_pwd();
	if (find_builtin_match(command, "env"))
		result = ft_env(env);
	if (find_builtin_match(command, "cd"))
		result = ft_cd(env, args);
	if (find_builtin_match(command, "export"))
		result = ft_export(env, args);
	if (find_builtin_match(command, "unset"))
		result = ft_unset(env, args);
	if (find_builtin_match(command, "exit"))
		result = ft_exit(args);
	free(command);
	return (result);
}
