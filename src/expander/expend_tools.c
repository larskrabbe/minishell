/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:06:50 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/04/06 18:36:57 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

/**
 * @brief gets you the value lenght from the variable 
 * 
 */
char	*get_value(char *str, t_env **env_lst, t_redirection *redirection)
{
	char	var_name[MAX_VAR_NAME];
	int		i;
	char	*ptr;

	i = 0;
	while (is_valid_var(str[i], i))
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i] = '\0';
	if (var_name[0] == '\0')
		return (ft_strdup("$"));
	if (var_name[0] == '?') {}
		return (ft_itoa(((int)(redirection->exit_code) >> 8) & 0x000000ff));
	ptr = ft_getenv(*env_lst, var_name);
	if (ptr == NULL)
		return (ft_strdup(""));
	return (ft_strdup(ptr));
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

int	at_eof(char *str, char *delimiter)
{
	if (!ft_strncmp(str, delimiter, ft_strlen(str)))
	{
		if (!ft_strncmp(str, delimiter, ft_strlen(delimiter)))
			return (TRUE);
	}
	return (FALSE);
}
