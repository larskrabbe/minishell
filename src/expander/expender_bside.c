/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender_bside.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:11:33 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/28 19:09:06 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

int	token_to_str(t_expend *exp, t_tokenchain *tokenchain, \
t_redirection *redirection, t_env **env_lst)
{
	exp->l = get_token_length(&tokenchain->token[exp->t], env_lst, redirection);
	exp->exe_ptr->argv[exp->arg_num] = ft_calloc(exp->l + 1, sizeof(char));
	if (exp->exe_ptr == NULL)
		return (error_allocation);
	get_token_str(&tokenchain->token[exp->t], env_lst, \
	exp->exe_ptr->argv[exp->arg_num], redirection);
	exp->arg_num++;
	exp->t++;
	return (0);
}

void	expander_setup(t_expend *exp, \
t_exe_data **exe_data)
{
	exp->exe_ptr = NULL;
	add_lst_t_exe_data(exe_data, &exp->exe_ptr);
	exp->error = 0;
	exp->t = 1;
	exp->arg_num = 0;
	exp->argv_flag = 0;
	exp->exe_data = exe_data;
}

int	choose_redirection(t_token *token, t_token *next, \
t_exe_data *exe_data, t_redirection *redirection)
{
	if (token->type == type_redirection)
		return (open_outfile(exe_data, next, redirection->env_lst, \
redirection));
	else if (token->type == type_app_redirection)
		return (open_outfile_app(exe_data, next, redirection->env_lst, \
redirection));
	else if (token->type == type_input_file)
		return (open_infile(exe_data, next, redirection->env_lst, redirection));
	else if (token->type == type_heredoc)
		return (heredoc(exe_data, next, redirection));
	return (0);
}

void	found_rediretion(t_tokenchain *tokenchain, \
t_expend *exp, t_redirection *redirection, \
t_exe_data *exe_data)
{
	if (tokenchain->token[exp->t].type != type_null && \
	tokenchain->token[exp->t].type >= type_redirection && \
	!exp->error)
	{
		exp->error = choose_redirection(&tokenchain->token[exp->t], \
		&tokenchain->token[exp->t + 1], exe_data, redirection);
		if (tokenchain->token[exp->t].type == type_pipe)
		{
			exp->arg_num = 0;
			add_lst_t_exe_data(exp->exe_data, &exp->exe_ptr);
		}
		else
			exp->t++;
	}
}
