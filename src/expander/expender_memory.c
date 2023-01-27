/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:54:20 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/27 16:04:30 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	free_str_in_token(t_tokenchain *tokenchain)
{
	int	i;

	i = 1;
	while (tokenchain->token[i].type != type_null)
	{
		if (tokenchain->token[i].type == type_str)
			free(tokenchain->token[i].str);
		tokenchain->token[i].type = type_null;
		i++;
	}
	if (tokenchain->token[i].type == type_str || \
	tokenchain->token[i].type == type_built_exe)
		free(tokenchain->token[i].str);
}
