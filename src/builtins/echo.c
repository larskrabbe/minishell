/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:10:00 by bogunlan          #+#    #+#             */
/*   Updated: 2022/12/15 21:13:28 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int is_arg_an_option(char *arg)
{
	if (!ft_strncmp("-n", arg, 2))
	{
		arg++;
		while (*arg)
		{
			if (*arg != 'n')
				return (0);
			arg++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(char **argv)
{
	int	option_count;
	int	i;

	i = 0;
	while (is_arg_an_option(argv[i]))
		option_count = ++i;
	if (option_count)
		argv += option_count;
	while (*argv)
	{
		if (*(argv + 1) != NULL)  
			printf("%s ", *argv);
		else
			printf("%s", *argv);
		argv++;
	}
	if (!option_count)
		printf("\n");
}