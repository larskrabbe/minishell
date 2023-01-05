/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:21:20 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/05 18:51:54 by bogunlan         ###   ########.fr       */
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
# define ARG_MAX 4096
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


/**
 * @brief 
 * 
 * @note the order and number are should not be changed  because i increament it in a funktion to 'upgrade' a type
 */
typedef enum e_ttype{
	type_null = 0,
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

int				is_white_space(int a);
int				is_special_char(char a);

void			myerror(char *str);
int				lexer(char *str, t_tokenchain *tokenchain);
t_tokenchain	*tokenchain_create(void);
void			print_token_chain(t_tokenchain *tokenchain);
void			free_str_in_token(t_tokenchain *tokenchain);
int				expander(t_tokenchain *tokenchain,t_env *env_lst);

/* 
====================================================
                      Environment                   
====================================================
 */
// The struct s_setenv is used to add a new environment variable
// It is used in add_var.c by the ft_setenv() function
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
void	env_add_back(t_env **env_lst, t_env *new_env);

/**
 * @brief  The ft_getenv_lst() fucntion obtains all names and 
 * values of the environment variable
 * 
 * @param envp
 * @return double pointer to t_env structure
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
void	ft_putenv(t_env *env_lst, char *name, char *value);

/**
 * @brief The find_env_match() function searches for a
 * matching environment variable name in the environment list.
 * @param env_lst 
 * @param name 
 * @return 1 is returned if a match is found,
 * 0 if there is no match
 */
int		find_env_match(t_env *env_lst, char *name);

/**
 * @brief The ft_setenv() function inserts or resets the environment
 * variable name in the current environment list
 * @return 1 if variable is added, otherwise 0
 */
int		ft_setenv(t_env *env_lst, char *new_env);

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
 * value of the environment variable whose name is provided
 * 
 * @param env_lst 
 * @param name
 * @return pointer to environment value, otherwise NULL
 */
char	*ft_getenv(t_env *env_lst, char *env_name);

/**
 * @brief The ft_gen_slice() function helps the ft_slice() function 
 * obtain an array of strings
 */
char	**ft_gen_slice(const char *s, char c, char **ptr, int ptr_index);

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
/**
 * @brief The ft_free() function deallocates memory from a **char
 * @param ptr pointer to be deallocated
 * @return NULL
 */
char	**ft_free(char **ptr);
/**
 * @brief The env_id_isvalid() function checks if a variable
 * has the right name
 * 
 * @param new_env_var 
 * @return  
 */
int	env_id_isvalid(char *new_env_var);

/**
 * @brief The invalid_env_id() function is an env_id_isvalid() helper
 * function that checks if the environment variable to be added has
 * the right naming convention
 * 
 * @param new_env 
 * @return
 */
int		invalid_env_id(char *new_env);

typedef struct s_env_string
{
	char			*name;
	char			*join_equal;
	char			*join_value;
}
				t_env_string;
/**
 * @brief The env_as_string() function gives a pointer to strings
 * of list of environment variables
 * 
 * @param env_lst 
 * @return char** 
 */
char	**env_as_string(t_env **env_lst);

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

/**
 * @brief The ft_pwd() prints the current working directory
 * 
 * @param env_lst 
 * @return returns an int defined by enum e_error
 */
int		ft_pwd(t_env **env_lst);
/**
 * @brief The ft_echo() function prints arguments passed
 * to it delimited by only a single space followed by a new line.
 * The new line is removed when the option -n is used
 * 
 * @param args 
 * @return returns an int defined by enum e_error
 */
int		ft_echo(char **args);
/**
 * @brief The ft_env() function prints a list of environment variables
 * 
 * @param env_lst 
 * @return returns an int defined by enum e_error
 */
int		ft_env(t_env **env_lst);
/**
 * @brief The ft_export() function adds valid variables to the list
 * of environment variables.
 * If the variable is already in the list, it is updated, else it is added.
 * When nothing is specified the list of environment variables is printed
 * 
 * @param env_lst 
 * @param new_env 
 * @return returns an int defined by enum e_error
 */
int		ft_export(t_env **env_lst, char **new_env);
/**
 * @brief The ft_unset() function deletes all specified variables from the
 * list of environment variables if it exists
 * 
 * @param env_lst 
 * @param env_name 
 * @return returns an int defined by enum e_error
 */
int		ft_unset(t_env **env_lst, char **env_name);

/**
 * @brief ft_cd() function changes the current directory
 * to the specified directory
 * 
 * @param env_lst 
 * @param path_name 
 * @return returns an int defined by enum e_error
 */
int		ft_cd(t_env **env_lst, char **path_name);
/**
 * @brief The cd_tilde_with_path() is an ft_cd() helper function to move 
 * into a directory in case the tilde (~) sign is used as a prefix.
 * An example is: ~/Documents/myfiles
 * 
 * @param env_lst 
 * @param path_name 
 * @return returns 1 if true, otherwise 0
 */
int		cd_tilde_with_path(t_env *env_lst, char **path_name);
/**
 * @brief The cd_error_mssg() function is an 
 * ft_cd() helper function that prints an error message
 * when the path provided is not valid
 * 
 * @param path_name 
 */
void	cd_error_mssg(char **path_name);
/**
 * @brief The set_old_pwd() function is an ft_cd() helper function
 * that sets the old pwd
 * 
 * @param env_lst 
 * @param pwd 
 */
void	set_old_pwd(t_env *env_lst, char *pwd);
/**
 * @brief The old_pwdis_set() function is 
 * ft_cd() helper function that checks if old pwd is
 * among the environment list upon first initialization of
 * all environment variables
 * @param env_lst 
 * @return returns 1 if true, otherwise 0
 */
int		old_pwdis_set(t_env *env_lst);

/* 
====================================================
                      Path                          
====================================================
 */

typedef struct	s_path
{
	char	*paths;
	char	*tmp_path;
	char	*join_fwd_slash;
	char	*new_path;
}
				t_path;

/**
 * @brief The get_cmd_path() function returns the path
 * of an executable file
 * 
 * @param env_lst 
 * @param cmd 
 * @return returns a pointer to char or NULL if no path was found
 */
char	*get_cmd_path(t_env **env_lst, char *cmd);


/* 
====================================================
                      Execution                     
====================================================
 */

/**
 * @brief The cmd_is_builtin() function checks if the passed
 * argument is a shell builtin
 * 
 * @return 1 if true, otherwise 0
 */
int		cmd_is_builtin(char *cmd);

#endif
