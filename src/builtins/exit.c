/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:04:13 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/27 12:57:37 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

long long int	my_atoli(const char *str)
{
	unsigned long long int	num;
	int						sign;
	int						i;
	unsigned long long int	last_num;

	sign = 1;
	num = 0;
	i = 0;
	last_num = num;
	while (is_white_space(str[i]))
		str++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		last_num = num;
		num = num * 10;
		num = num + (str[i] - '0');
		i++;
		if (num < last_num && last_num != 0)
			return (-1);
	}
	if (sign == -1 && num * sign < last_num * sign)
		return (-1);
	if (sign == 1 && num * sign > last_num * sign)
		return (-1);
	return (sign * num);
}
//			printf("%s: exit: %s: numeric argument required", IDLE_PROMT, str);

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
		if (!ft_isdigit(exit_code[i])) //needs to check full string
		{
			printf("%s: exit: %c: numeric argument required\n", \
			IDLE_PROMT, *exit_code);
			return (error_exit);
		}
		i++;
	}
	long long int num = 9223372036854775806;
	printf("nnum%lli\n",num);
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
