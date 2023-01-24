/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:00:28 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/24 23:02:32 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

typedef struct s_exp_env{
	char	*ptr;
	int		q;
	char	*var_ptr;
	int		l;
	int		i;
}t_exp_env;

/**
 * @brief funktion for telling if a char 
 * is valid at the current position for env vars
 * 
 * @param c the char
 * @param i the position of the the char in the var name
 * 
 * @return returns 1 it valid or 0 if  invalid
 */
int	is_valid_var(char c, int i)
{
	if (c == '?' && i == 0)
		return (1);
	if (ft_isalpha(c))
		return (1);
	if (ft_isdigit(c) && i != 0)
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void	get_len_exp(t_exp_env *exp, t_env *env_lst, t_redirection *redirection)
{
	exp->i = 0;
	exp->ptr++;
	exp->l += strlen_with_check(get_value(exp->ptr, env_lst, redirection));
	while (is_valid_var(*exp->ptr, exp->i))
	{
		exp->ptr++;
		exp->i++;
	}
	exp->ptr--;
}

int	get_token_length(t_token *token, t_env *env_lst, t_redirection *redirection)
{
	struct s_exp_env	exp;

	exp.q = 0;
	exp.ptr = token->start;
	exp.l = 0;
	while (exp.ptr != token->end)
	{
		if ((*exp.ptr == '"' || *exp.ptr == '\'' ) && exp.q == 0)
			exp.q = *exp.ptr;
		else if ((*exp.ptr == '"' || *exp.ptr == '\'' ) && exp.q == *exp.ptr)
			exp.q = 0;
		else if (*exp.ptr == '$' && exp.q != '\'')
			get_len_exp(&exp, env_lst, redirection);
		else
			exp.l++;
		exp.ptr++;
	}
	return (exp.l + 1);
}

void	get_value_exp(t_exp_env *exp, char *str, \
t_env *env_lst, t_redirection *redirection)
{
	exp->ptr++;
	exp->i = 0;
	exp->var_ptr = get_value(exp->ptr, env_lst, redirection);
	while (exp->var_ptr != NULL && *exp->var_ptr != '\0')
	{
		str[exp->l] = *exp->var_ptr;
		exp->var_ptr++;
		exp->l++;
	}
	while (is_valid_var(*exp->ptr, exp->i))
	{
		exp->ptr++;
		exp->i++;
	}
	exp->ptr--;
}

void	get_token_str(t_token *token, t_env *env_lst, \
char *str, t_redirection *redirection)
{
	struct s_exp_env	exp;

	exp.l = 0;
	exp.q = 0;
	exp.ptr = token->start;
	while (exp.ptr != token->end)
	{
		if ((*exp.ptr == '"' || *exp.ptr == '\'' ) && exp.q == 0)
			exp.q = *exp.ptr;
		else if ((*exp.ptr == '"' || *exp.ptr == '\'' ) && exp.q == *exp.ptr)
			exp.q = 0;
		else if (*exp.ptr == '$' && exp.q != '\'')
			get_value_exp(&exp, str, env_lst, redirection);
		else
		{
			str[exp.l] = *exp.ptr;
			exp.l++;
		}
		exp.ptr++;
	}
	str[exp.l] = '\0';
}
