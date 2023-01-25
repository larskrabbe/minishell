/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:04:13 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/25 18:05:13 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	time_to_exit(char *exit_code)
{
	int	i;

	printf("exit\n");
	g_signal = signal_d;
	i = 0;
	if (!exit_code)
		return (0);
	while (exit_code[i] != '\0')
	{
		if (!ft_isdigit(exit_code[i]))
		{
			printf("%s: exit: %c: numeric argument required\n", \
			IDLE_PROMT, *exit_code);
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
		printf("%s: exit: too many arguments\n",IDLE_PROMT);
		return (error_builtin);
	}
	else
		exit_code = time_to_exit(*args);
	return (exit_code);
}
