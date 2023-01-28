/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:04:13 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/27 21:06:29 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	my_atoli_helper(const char *str, int *i, unsigned long long *num)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*num = *num * 10;
		*num = *num + (str[*i] - '0');
		(*i)++;
		if ((*num) > 9223372036854775807)
		{
			printf("%s: exit: %s: numeric argument required\n", IDLE_PROMT, str);
			return (error_exit);
		}
	}
	return (no_error);
}

unsigned char	my_atoli(const char *str)
{
	unsigned long long int	num;
	int						sign;
	int						i;
	unsigned long long int	last_num;

	sign = 1;
	num = 0;
	last_num = 0;
	i = 0;
	while (is_white_space(str[i]))
		str++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	if (my_atoli_helper(str, &i, &num) == error_exit)
		return (error_exit);
	if (sign == -1)
		num = -num;
	return ((unsigned char)(num));
}

int	time_to_exit(char *exit_code)
{
	int	i;

	printf("exit here\n");
	i = 0;
	if (!exit_code)
		return (0);
	if (exit_code[0] == '-' || exit_code[0] == '+')
		i = 1;
	else
		i = 0;
	while (exit_code[i] != '\0')
	{
		if (!ft_isdigit(exit_code[i]))
		{
			printf("%s: exit: %s: numeric argument required\n", \
			IDLE_PROMT, exit_code);
			return (error_exit);
		}
		i++;
	}
	return (my_atoli(exit_code));
}

int	ft_exit(char **args)
{
	int	exit_code;

	g_signal = signal_d;
	if (!*args)
	{
		printf("exit\n");
		return (0);
	}
	if (*(args + 1) != NULL && ft_isdigit(**args))
	{
		g_signal = 1;
		printf("%s: exit: too many arguments\n", IDLE_PROMT);
		return (error_builtin);
	}
	else
		exit_code = time_to_exit(args[0]);
	return (exit_code);
}
