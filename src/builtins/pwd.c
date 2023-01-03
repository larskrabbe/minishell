/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:40:05 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/03 18:46:02 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_env **env_lst)
{
	char	*pwd;

	if (!env_lst)
		return (error_allocation);
	pwd = ft_getenv(*env_lst, "PWD");
	if (!pwd)
		return (error_allocation);
	printf("%s\n", pwd);
	return (no_error);
}
