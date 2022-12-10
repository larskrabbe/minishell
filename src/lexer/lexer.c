	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:50:17 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/03 19:27:40 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"lexer.h"

void inline static	quotes_logic(char c, char *end)
{
	if (c == '\"' && *end == ' ')
		*end = '\"';
	else if (c == '\'' && *end == ' ')
		*end = '\'';
	else if (c == '\"' && *end == '\"')
		*end = ' ';
	else if (c == '\'' && *end == '\'')
		*end = ' ';
}

char	*find_token_end(char *str)
{
	char	end;

	end = ' ';
	while (*str != '\0' && (*str != end || end != ' '))
	{
		quotes_logic(*str, &end);
		str++;
	}
	quotes_logic(*str, &end);
	if (end != ' ')
		return (NULL);
	return (str++);
}

int	lexer(char *str, t_tokenchain *tokenchain)
{
	int	i;
	int	t;

	i = 0;
	t = 1;
	tokenchain->str = str;
	while (*str != '\0')
	{
		if (is_white_space(*str) == 0)
		{
			tokenchain->token[t].start = str;
			tokenchain->token[t].end = find_token_end(&str[i]);
			str = tokenchain->token[t].end;
			if (tokenchain->token[t].end == NULL)
				myerror("quotes not closed");
			t++;
		}
		if (*str != '\0')
			str++;
	}
	return (0);
}
