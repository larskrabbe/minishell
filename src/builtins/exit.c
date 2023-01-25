/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:04:13 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/25 16:14:28 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	time_to_exit(char *exit_code)
{
	int	i;

	printf("exit\n");
	g_signal = 0;
	i = 0;
	if (!exit_code)
		return (0);
	while (exit_code[i] != '\0')
	{
		if (!ft_isdigit(exit_code[i]))
		{
			printf("<minishell>: exit: %c: numeric arg required\n", *exit_code);
			return (error_exit);
		}
		i++;
	}
	return (ft_atoi(exit_code));
}

int	ft_exit(char **args)
{
	int	exit_code;

	if (!args)
		exit_code = time_to_exit(NULL);
	if (*(args + 1) != NULL && ft_isdigit(**args))
	{
		printf("Hey! too many arguments>> %s\n",*(args + 1));
		return (error_builtin);
	}
	else
		exit_code = time_to_exit(*args);
	return (exit_code);
}
