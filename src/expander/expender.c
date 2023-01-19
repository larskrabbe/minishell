/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:08:19 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/19 12:21:13 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	"../../include/minishell.h"

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
			token->type++;
		if (*(token->start + 2) != *token->end && \
		(*(token->start + 1) == *token->start))
			return (error_syntax);
	}
	else
			token->type = type_str;
	return (0);
}

/**
 * @brief funktion for telling if a char is valid at the current position for env vars
 * 
 * @param c the char
 * @param i the position of the the char in the var name
 * 
 * @return returns 1 it valid or 0 if  invalid
 */
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
 * @brief strlen with check for null
 * 
 */
int	strlen_with_check(char *str)
{
	if (str == NULL)
		return (0);
	return (ft_strlen(str));
}

/**
 * @brief gets you the value lenght from the variable 
 * 
 */
char	*get_value(char *str, t_env *env_lst)
{
	char	var_name[MAX_VAR_NAME];
	int		i;

	printf("get value %s\n", str);
	i = 0;
	while (is_valid_var(str[i], i))
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i] = '\0';
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
			l += strlen_with_check(get_value(ptr, env_lst));
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
	return (l + 1);
}

char *tokenstring(t_token *token, t_env *env_lst)// need a way to return error message
{
	int		len;
	char	*str;

	str = NULL;
	len = get_token_length(token, env_lst);
	if (str == NULL)
		return (NULL);
	get_token_str(token, env_lst, str);
	return (str);
}
void	get_token_str(t_token *token, t_env *env_lst, char *str)
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
			while (var_ptr != NULL && *var_ptr != '\0')
			{
				str[l] = *var_ptr;
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
			str[l] = *ptr;
			l++;
		}
		ptr++;
	}
	str[l] = '\0';
}

int	add_lst_t_exe_data(t_exe_data **exe_data, t_exe_data **exe_ptr)
{
	if (*exe_data == NULL)
	{
		printf("first\n");
		*exe_data = ft_calloc(1, sizeof(t_exe_data));
		*exe_ptr = *exe_data;
		printf("first\n");
	}
	else
	{
		printf("extra\n");
		(*exe_ptr)->next = ft_calloc(1, sizeof(t_exe_data));
		*exe_ptr = (*exe_ptr)->next;
		printf("extra fin\n");
	}
	if (*exe_data == NULL || *exe_ptr == NULL)
		return (error_allocation);
	(*exe_ptr)->fd_read = -1;
	(*exe_ptr)->fd_write = -1;
	return (0);
}

// int	redirection(t_exe_data *exe_ptr, t_token *token, int type)
// {

// 	if (tokenchain->token[t].type == type_pipe)
// 	{
// 		exe_ptr->argv[arg_num] = NULL;
// 		arg_num = 0;
// 	}
// 	return (0);
// }

int	expander(t_tokenchain *tokenchain, t_env *env_lst, t_exe_data **exe_data, t_redirection *redirection)
{
	int			t;
	int			l;
	int			arg_num;
	t_exe_data	*exe_ptr;

	exe_ptr = NULL;
	t = 1;
	arg_num = 0;

	add_lst_t_exe_data(exe_data, &exe_ptr);
	while (tokenchain->token[t].start != NULL)
	{
		printf("in expander\n");
		// if (tokenchain->token[t].start != NULL && check_type(&tokenchain->token[t]) != 0)// shold be in the tokenizer
		// add_lst_t_exe_data(exe_data, &exe_ptr);
		// 	return (1);
		while (tokenchain->token[t].start != NULL && tokenchain->token[t].type <= type_str)// will be his own funktion
		{
			l = get_token_length(&tokenchain->token[t], env_lst);
			exe_ptr->argv[arg_num] = ft_calloc(l + 1, sizeof(char));
			printf("copy argv %i|",arg_num);
			if (exe_ptr == NULL)
				return (error_allocation);
			get_token_str(&tokenchain->token[t], env_lst, exe_ptr->argv[arg_num]);
			arg_num++;
			t++;
		}
		if (tokenchain->token[t].start != NULL && tokenchain->token[t].type >= type_redirection && tokenchain->token[t].type != type_pipe)// will be his own funktion
		{
			printf("redirect\n");// need to check if the next type == str
			if (tokenchain->token[t].type == type_heredoc)
				heredoc(tokenstring(&tokenchain->token[t + 1], env_lst));
			if (tokenchain->token[t].type == type_input_file)
				redirection->infile = tokenstring(&tokenchain->token[t + 1], env_lst);
			if (tokenchain->token[t].type == type_redirection)
				redirection->outfile = tokenstring(&tokenchain->token[t + 1], env_lst);
			if (tokenchain->token[t].type == type_app_redirection)
				redirection->outfile = tokenstring(&tokenchain->token[t + 1], env_lst);
			t++;
		}
		else if (tokenchain->token[t].type == type_pipe)
		{
			printf("pipe\n");
			arg_num = 0;
			add_lst_t_exe_data(exe_data, &exe_ptr);
		}
		t++;
	}
	return (0);
}
