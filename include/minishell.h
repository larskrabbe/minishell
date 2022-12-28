/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe < lkrabbe@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:21:20 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/24 15:09:50 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H

//?-----------Includes------------?//

# include	<stdio.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<signal.h>
# include	"libft.h"
# include	"../src/lexer/lexer.h"
# include	"../src/expander/expender.h"

//?-----------Defines------------?//

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

//!max amount of 'token' not sure if needed
# define ARG_MAX 1000
# define MAX_VAR_NAME 1000

//?-----------ENUMS------------?//

/**
 * @brief enums for error values
 * 
 */
typedef enum e_error{
	no_error = 0,
	error_quotes = 1,
	error_allocation = 2,
	error_max_arg = 3,
	error_syntax = 4,
}t_error;


typedef enum e_signal{
	no_signal = 0,
	exit_signal = 1,
	c_signal = 2,
}t_sigal;

typedef enum e_ttype{
	type_built_exe = 1,
	type_str = 2,
	type_redirection = 3,
	type_app_redirection = 4,
	type_input_file = 5,
	type_heredoc = 6,
	type_pipe = 10,
}t_ttype;


/**
 * @brief stores each position of a token inside of the input string
 * 
 * @param tokentype int that represent the type of token
 * @param start the start of the token
 * @param end the end of the token
 */
typedef struct s_token{
	char			*start;
	char			*end;
	char			*str;
	int				type;
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

typedef struct	s_env
{
char			*name;
char			*value;
struct s_env	*next;
}					t_env;

//?-----------PROTOTYPES------------?//

int			is_white_space(int a);
int			is_special_char(char a);

void			myerror(char *str);
int				lexer(char *str, t_tokenchain *tokenchain);
t_tokenchain	*tokenchain_create(void);
void			print_token_chain(t_tokenchain *tokenchain);

int	expander(t_tokenchain *tokenchain,t_env *env_lst);

/* 
====================================================
                      Environment                   
====================================================
 */
// The s_setenv is used to add a new environment variable
// It is used in add_var.c by the ft_setenv function
typedef struct s_setenv
{
	char	*name;
	char	*value;
	char	**split;
	t_env	*env_curr;
}				t_setenv;

/**
 * @brief The env_lstnew() function creates a new
 * node for a linked list structure to store every
 * environment variable
 * 
 * @param content 
 * @return t_env* 
 */
t_env	*env_lstnew(char *content);

/**
 * @brief The env_add_back() function adds every new
 * node created to a linked list structure that stores
 * environment variables
 * @param lst 
 * @param new 
 */
void	env_add_back(t_env **lst, t_env *new_env);

/**
 * @brief  The ft_getenv_lst() fucntion obtains all names and 
 * values of the environment variable
 * 
 * @param envp 
 */
t_env	**ft_getenv_lst(char **envp);

/**
 * @brief The ft_printenv() function prints out the names and
 * values of the variables in the environment
 * 
 * @param env_lst 
 */
void	ft_printenv(t_env *env_lst);

/**
 * @brief  The ft_putenv() function takes an argument of
 * the form ``name=value'' and adds it to the environment
 * list
 * ft_setenv()
 */
void	ft_putenv(t_env *env_list, char *name, char *value);

/**
 * @brief The find_env_match searches for a matching name
 * in the environment list. 1 is returned if found and 0 
 * if there is no match
 * @param env_list 
 * @param name 
 * @return int 
 */
int		find_env_match(t_env *env_list, char *name);

/**
 * @brief The ft_setenv() function inserts or resets the environment
 * variable name in the current environment list
 * 
 */
int		ft_setenv(t_env *env_list, char *new_env);

/**
 * @brief  The ft_unsetenv() function deletes all instances of the
 * variable name pointed to by name from the environment list
 * 
 * @param env_lst 
 * @param name 
 */
void	ft_unsetenv(t_env **env_lst, char *name);

/**
 * @brief The ft_getenv() function obtains the current
 * value of the environment variable, name.
 * 
 * @param env_lst 
 * @param name 
 */
char	*ft_getenv(t_env *env_lst, char *name);

/**
 * @brief The ft_gen_slice() function helps the ft_slice() function 
 * obtain an array of strings
 */
char	**ft_gen_slice(const char *s, char c, char **res, int res_s_i);

/**
 * @brief The clean_env frees all dynamically allocated memory used
 * in creating an environment list
 * 
 * @param env_lst 
 */
void	clean_env(t_env **env_lst);

/**
 * @brief The ft_slice() function splits a string at the point of the 
 * first matching character provided as the delimiter
 * @param s string to be sliced
 * @param c delimeter
 */
char	**ft_slice(char const *s, char c);
char	**ft_free(char **res);

// char		*ft_strjoin(char const *s1, char const *s2);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// size_t	ft_strlen(const char *s);


/* 
====================================================
                      BuiltIns                   
====================================================
 */

// The s_cd structure is used for the cd builtin
typedef struct s_cd
{
	char	pwd[256];
	char	*old_pwd;
	char	*new_pwd;
	char	*new_path;
	char	*tmp;
	char	*rest_of_path;
	int		res;
}				t_cd;

int		ft_pwd(t_env **env_lst);
int		ft_echo(char **args);
int		ft_env(t_env **env_lst);
int		ft_export(t_env **env_lst, char *new_env);
int		ft_unset(t_env **env_lst, char *name);

int		ft_cd(t_env **env_lst, char **path_name);
int		cd_tilde_with_path(t_env *env_lst, char **path_name);
void	set_old_pwd(t_env *env_lst, char *pwd);
void	cd_old_error(char **path_name);
void	set_old_pwd(t_env *env_lst, char *pwd);
int		old_pwdis_set(t_env *env_lst);

#endif
