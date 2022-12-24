/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe < lkrabbe@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:08:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/24 12:22:20 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../../include/minishell.h"

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
		if (*(token->start + 1) == *token->start)
			token->type++;
		if (*(token->start + 2) != *token->end && (*(token->start + 1) == *token->start))
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

// int	get_envvar_len(char *var_name,);
// {
// 	char *t;
	
// 	t = ft_getenv();
	
// }

int	get_token_length(t_token *token, t_env *env_lst)
{
	int		l;
	char	*ptr;
	int		q;

	q = 0;
	ptr = token->start;
	l = 0;
	while (ptr != token->end)
	{
		if ((*ptr == '"' || *ptr == '\'' ) && q == 0)
			q = *ptr;
		else if ((*ptr == '"' || *ptr == '\'' ) && q == *ptr)
			q = 0;
		else if (*ptr == '$' && q != '\'')
		{
			l += ft_strlen( ft_getenv(env_lst,ptr));
			printf(">>env\n");
		}
		else
			l++;
		ptr++;
	}
	return (0);
}

int	expander(t_tokenchain *tokenchain, t_env *env_lst)
{
	int	t;

	t = 1;
	while (tokenchain->token[t].start != NULL)
	{
		if (check_type(&tokenchain->token[t]) != 0)
			return (1);
		if (tokenchain->token[t].type <= type_str)
		{
			get_token_length(&tokenchain->token[t], env_lst);
		}
		t++;
	}
	return (0);
}
