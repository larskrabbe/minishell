/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:54:20 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/19 20:39:31 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

void	free_str_in_token(t_tokenchain *tokenchain)
{
	int	i;

	i = 1;
	while (tokenchain->token[i].end == NULL)
	{
		if (tokenchain->token[i].type == type_str || \
		tokenchain->token[i].type == type_built_exe)
		{			
			printf("free this => %s\n", tokenchain->token[i].str);
			free(tokenchain->token[i].str);
		}	
		tokenchain->token[i].type = type_null;
		i++;
	}
	if (tokenchain->token[i].type == type_str || \
	tokenchain->token[i].type == type_built_exe)
	{			
		//printf("free this => %s\n", tokenchain->token[i].str);
		free(tokenchain->token[i].str);
	}
}
