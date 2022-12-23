/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:40:05 by bogunlan          #+#    #+#             */
/*   Updated: 2022/12/23 18:02:27 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_env **env_lst)
{
	char	*pwd;

	pwd = ft_getenv(*env_lst, "PWD");
	if (!pwd)
		return (0);
	printf("%s\n", pwd);
	return (1);
}
