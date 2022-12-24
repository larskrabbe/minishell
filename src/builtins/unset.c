/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:35:10 by bogunlan          #+#    #+#             */
/*   Updated: 2022/12/23 18:42:37 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(t_env **env_lst, char *name)
{
	if (name && ((*name >= 33 && *name <= 64)
			|| (*name >= 91 && *name <= 94)
			|| (*name >= 123 && *name <= 127))
	)
	{
		printf("unset %s: not a valid identifier\n", name);
		return (0);
	}
	ft_unsetenv(env_lst, name);
	return (1);
}
