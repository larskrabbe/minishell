/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:24:10 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/08 18:11:48 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEXER_H
# define LEXER_H

//?-----------Includes------------?//

# include	"../../include/minishell.h"

//?-----------Defines------------?//

//!max amount of 'token' not sure if needed
# define ARG_MAX 1000

//?-----------Enums------------?//

/**
 * @brief enums to for each token, mostly used in the tokenizer
 * 
 */
typedef enum e_toektype{
	token_end = 0,
	token_start = 1,
}t_tokentype;

/**
 * @brief enums to for each token, mostly used in the tokenizer
 * 
 */
typedef enum e_quotes{
	noquotes = 0,
	squotes = 1,
	dquotes = 2,
}t_quotes;

//?-----------Structs------------?//

/**
 * @brief stores each position of a token inside of the input string
 * 
 * @param tokentype int that represent the type of token
 * @param start the start of the token
 * @param end the end of the token
 */
typedef struct s_token{
	char		*start;
	char		*end;
}t_token;

/**
 * @brief Head structure of the tokenchain
 * 
 * @param str string that is tokenize
 * @param tokenchain the pointer to all token
 */
typedef struct s_tokenchain{
	char	*str;
	t_token	*token;
}t_tokenchain;

//?-----------Protoypes------------?//

void			myerror(char *str);
int				lexer(char *str, t_tokenchain *tokenchain);
t_tokenchain	*tokenchain_create(void);
void			print_token_chain(t_tokenchain *tokenchain);

#endif