/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:08:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/13 21:40:03 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"expender.h"

int	check_type(t_token *token)
{
	static int	exe = FALSE;

	if (is_special_char(*token->start))
	{
		if (*token->start == '>')
			token->type = type_redirection;
		else if (*token->start == '<')
			token->type = type_input_file;
		else if (*token->start == '|')
			token->type = type_pipe;
		else
			printf("missing type for %c\n", *token->start);
		if (*token->start + 1 == *token->start)
			token->type++;
		if (*token->start + 2 != *token->end)
			return (error_syntax);
	}
	else
	{
		if (exe == FALSE)
		{
			token->type = type_str;
			exe = TRUE;
		}
		else
			token->type = type_built_exe;
	}
	if (token->type == type_pipe)
		exe = FALSE;
	return (0);
}

int	expend(t_token *token);
{
	int	l;

	l = 0;
	i++;
	while (token.start + i != token.end)
	{
		if (*token.start == '"' || *token.start == '\'')
			
		if else
		
		else
		i++;
	}
	return (0);
}

int	f1(t_tokenchain *tokenchain)
{
	int	t;

	t = 0;
	while (tokenchain->token[t].end != NULL)
	{
		if (check_type(tokenchain->token) != 0)
			return (1);
		if (tokenchain->token->type <= type_str)
		{
			expend();
		}
		t++;
	}
	return (0);
}
