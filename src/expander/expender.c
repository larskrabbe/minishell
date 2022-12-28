/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe < lkrabbe@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:08:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/27 19:46:03 by lkrabbe          ###   ########.fr       */
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

int	is_valid_var(char c, int i)
{
	if (ft_isalpha(c))
		return (1);	
	if (ft_isdigit(c) && i != 0)
		return (1);	
	if (c == '_')
		return (1);	
	return(0);
}

int	get_envvar_len(char *var_name, t_env *env_lst)
{
	char	buffer[MAX_VAR_NAME];
	int		i;
	
	i = 0;
	while (is_valid_var(var_name[i],i))
	{
		buffer[i] = var_name[i];		
		i++;
	}
	buffer[i] = '\0';
	return(ft_strlen( ft_getenv(env_lst, buffer)));
}

int	get_token_length(t_token *token, t_env *env_lst)
{
	int		l;
	char	*ptr;
	int		q;
	int		i;

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
			i = 0;
			ptr++;
			l += get_envvar_len(ptr,env_lst);
			while (is_valid_var(*ptr,i))
			{
				ptr++;
				i++;
			}
			ptr--;
		}
		else
			l++;
		ptr++;
	}
	return (l);		
}

int	expander(t_tokenchain *tokenchain, t_env *env_lst)
{
	int	t;
	int	l;

	t = 1;
	while (tokenchain->token[t].start != NULL)
	{
		if (check_type(&tokenchain->token[t]) != 0)
			return (1);
		if (tokenchain->token[t].type <= type_str)
		{
			l = get_token_length(&tokenchain->token[t], env_lst);
			ft_calloc(l,sizeof(char));
			
		}
		t++;
	}
	return (0);
}
