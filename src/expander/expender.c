/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:08:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/28 20:09:22 by lkrabbe          ###   ########.fr       */
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
	return (0);
}

/**
 * @brief returns the value len
 * 
 */
int	get_env_value_len(t_env	*env_lst, char *var)
{
	char	*ptr;
	int		l;

	l = 0;
	ptr = ft_getenv(env_lst, var);
	printf("value = %s\n", ptr);
	if (ptr == NULL)
		return (0);
	while (ptr[l] != '\0')
		l++;
	return (l);
}

/**
 * @brief gets you the value lenght from the variable 
 * 
 */
char	*get_value(char *str, t_env *env_lst)
{
	char	var_name[MAX_VAR_NAME];
	int		i;

	i = 0;
	while (is_valid_var(str[i], i))
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i] = '\0';
	printf("var_name = %s\n",var_name);
	return (ft_getenv(env_lst, var_name));
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
			l += get_env_value_len(env_lst, get_value(ptr, env_lst));
			while (is_valid_var(*ptr, i))
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

void	get_token_str(t_token *token, t_env *env_lst)
{
	char	*ptr;
	int		q;
	char	*var_ptr;
	int		l;
	int		i;

	l = 0;
	q = 0;
	ptr = token->start;
	while (ptr != token->end)
	{
		if ((*ptr == '"' || *ptr == '\'' ) && q == 0)
			q = *ptr;
		else if ((*ptr == '"' || *ptr == '\'' ) && q == *ptr)
			q = 0;
		else if (*ptr == '$' && q != '\'')
		{
			ptr++;
			i = 0;
			var_ptr = get_value(ptr, env_lst);
			//printf("??%s",var_ptr);
			while (var_ptr != NULL && *var_ptr != '\0')
			{
				token->str[l] = *var_ptr;
				var_ptr++;
				l++;
			}
			while (is_valid_var(*ptr, i))
			{
				ptr++;
				i++;
			}
			ptr--;
		}
		else
		{
			token->str[l] = *ptr;
			l++;
		}
		ptr++;
	}
	//token->str[l] = '\0';
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
			tokenchain->token[t].str = ft_calloc(l, sizeof(char));
			if (tokenchain->token[t].str == NULL)
				return (error_allocation);
			get_token_str(&tokenchain->token[t], env_lst);
			printf(">>%s\n",tokenchain->token[t].str);
		}
		t++;
	}
	return (0);
}
