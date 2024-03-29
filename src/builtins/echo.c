/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:10:00 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/23 13:27:27 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_arg_an_option(char *arg)
{
	if (!ft_strncmp("-n", arg, 2))
	{
		arg++;
		while (*arg)
		{
			if (*arg != 'n')
				return (FALSE);
			arg++;
		}
		return (TRUE);
	}
	return (FALSE);
}

void	ft_echo_args(char **args)
{
	while (*args)
	{
		if (*(args + 1) != NULL)
		{
			printf("%s ", *args);
		}
		else
			printf("%s", *args);
		args++;
	}
}

int	ft_echo(char **args)
{
	int		option_count;
	int		i;

	i = 0;
	option_count = 0;
	if (!args)
		return (0);
	if (args)
		while (args[i] && is_arg_an_option(args[i]))
			option_count = ++i;
	args += option_count;
	if (args)
		ft_echo_args(args);
	if (!option_count)
		printf("\n");
	return (no_error);
}
