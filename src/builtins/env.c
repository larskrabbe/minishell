/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:02:32 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/26 18:57:19 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	ft_env(t_env **env_lst)
{
	
	if (!env_lst)
		return (error_allocation);
	if (*env_lst)
		ft_printenv(*env_lst);
	return (no_error);
}
