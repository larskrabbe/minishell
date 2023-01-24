/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:06:50 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/24 23:08:55 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

/**
 * @brief gets you the value lenght from the variable 
 * 
 */
char	*get_value(char *str, t_env *env_lst, t_redirection *redirection)
{
	char	var_name[MAX_VAR_NAME];
	int		i;

	i = 0;
	while (is_valid_var(str[i], i))
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i] = '\0';
	if (var_name[0] == '\0')
		return (ft_itoa((int)getpid()));
	if (var_name[0] == '?')
		return (ft_itoa(((int)(redirection->exit_code) >> 8) & 0x000000ff));
	return (ft_getenv(env_lst, var_name));
}

/**
 * @brief strlen with check for null
 * 
 */
int	strlen_with_check(char *str)
{
	if (str == NULL)
		return (0);
	return (ft_strlen(str));
}
