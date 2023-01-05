/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:02:32 by bogunlan          #+#    #+#             */
/*   Updated: 2023/01/03 18:38:07 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	ft_env(t_env **env_lst)
{
	if (!env_lst)
		return (error_allocation);
	ft_printenv(*env_lst);
	return (no_error);
}
