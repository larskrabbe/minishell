/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:08:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/26 17:58:09 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	check_type(t_token *token)
{
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
		if (*(token->start + 1) == *token->start)
		{
			token->type++;
			if (*(token->start + 2) != *token->end && \
			(*(token->start + 1) == *token->start))
				return (error_syntax);
		}
	}
	else
			token->type = type_str;
	return (0);
}

char	*tokenstring(t_token *token, t_env *env_lst, \
t_redirection *redirection)
{
	int		len;
	char	*str;

	str = NULL;
	len = get_token_length(token, env_lst, redirection);
	str = ft_calloc(len, sizeof(char));
	if (str == NULL)
		return (NULL);
	get_token_str(token, env_lst, str, redirection);
	return (str);
}

int	add_lst_t_exe_data(t_exe_data **exe_data, t_exe_data **exe_ptr)
{
	if (*exe_data == NULL)
	{
		*exe_data = ft_calloc(1, sizeof(t_exe_data));
		*exe_ptr = *exe_data;
	}
	else
	{
		(*exe_ptr)->next = ft_calloc(1, sizeof(t_exe_data));
		*exe_ptr = (*exe_ptr)->next;
	}
	if (*exe_data == NULL || *exe_ptr == NULL)
		return (error_allocation);
	(*exe_ptr)->fd_read = -1;
	(*exe_ptr)->fd_write = -1;
	(*exe_ptr)->pid = -1;
	return (0);
}

/**
 * @brief set the values inside of the struct back to zero
 * 
 */
void	redirection_default(t_redirection *redirection)
{
	redirection->fd_infile = -1;
	redirection->fd_outfile = -1;
}

int	expander(t_tokenchain *tokenchain, t_env *env_lst, \
t_redirection *redirection)
{
	struct s_expend	exp;

	expander_setup(&exp, redirection, &redirection->og_ptr);
	while (tokenchain->token[exp.t].start != NULL && !exp.error)
	{
		while (tokenchain->token[exp.t].type == type_str && \
		!exp.error && exp.argv_flag == 0)
			exp.error = token_to_str(&exp, tokenchain, redirection, env_lst);
		if (exp.arg_num != 0 && !exp.error)
			exp.exe_ptr->argv[exp.arg_num] = NULL;
		found_rediretion(tokenchain, &exp, redirection, env_lst);
		if (tokenchain->token[exp.t].type != type_null)
			exp.t++;
	}
	return (exp.error);
}
