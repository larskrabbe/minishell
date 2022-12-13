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

int inline static	quotes_logic(char c, char *end)
{
	if (c == '\"' && *end == ' ')
		*end = '\"';
	else if (c == '\'' && *end == ' ')
		*end = '\'';
	else if (c == '\"' && *end == '\"')
		*end = ' ';
	else if (c == '\'' && *end == '\'')
		*end = ' ';
	else if (*end == ' ' && is_special_char(c))
	{
		// printf("S char at the end\n");
		return (1);
	}
	return (0);
}

char	*find_token_end(char *str)
{
	char	end;

	end = ' ';
	if (is_special_char(*str) != 0)
		return (str + 1);
	while (*str != '\0' && (*str != end || end != ' '))
	{
		if (quotes_logic(*str, &end))
			return (str);
		str++;
	}
	if (end != ' ')
		return (NULL);
	if (quotes_logic(*str, &end) == 1)
		return (str);
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
			tokenchain->token[t].end = find_token_end(str);
			str = tokenchain->token[t].end;
			if (tokenchain->token[t].end == NULL)
				return (error_quotes);
			t++;
		}
		else
			str++;
	}
	return (0);
}
