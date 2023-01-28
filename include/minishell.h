/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:21:20 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/28 15:52:10 by lkrabbe          ###   ########.fr       */
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
# include	<fcntl.h>
# include	<termios.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<unistd.h>

//?----------Globals------------?//

int	g_signal;

//?-----------Defines------------?//

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

//!max amount of 'token' not sure if needed
# define MAX_ARG 4096
# define MAX_VAR_NAME 1000
# define MAX_FILENAME 256
# define MAX_PATH 4096
# define IDLE_PROMT "<minishell>"
# define HEREDOC_PROMT "> "
// # define MAX_EXE 100 // not sure if this is a good idea 
//?-----------ENUMS------------?//

/**
 * @brief enums for error values
 * 
 */
typedef enum e_error{
	no_error = 0,
	error_quotes = 1,
	error_syntax = 2,
	error_allocation ,
	error_max_arg ,
	error_null_ptr ,
	error_pipe ,
	error_open ,
	error_permission ,
	error_close ,
	error_nofile ,
	error_execve ,
	error_direct,
	error_exit = 255,
	error_builtin = 256,
}t_error;

typedef enum e_signal{
	no_signal = 0,
	signal_default = 1,
	signal_escape = 10,
	signal_d = 20,
	signal_c = 30,
}t_sigal;

/**
 * @brief 
 * 
 * @note the order and number are should not be changed 
 *  because i increament it in a funktion to 'upgrade' a type
 */
typedef enum e_ttype{
	type_null = 0,
	type_built_exe = 1,
	type_str = 2,
	type_redirection = 10,
	type_app_redirection = 11,
	type_input_file = 12,
	type_heredoc = 13,
	type_pipe = 20,
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

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_exe_data{
	char				*argv[MAX_ARG];
	char				*path;
	int					fd_read;
	int					fd_write;
	struct s_exe_data	*next;
	int					pid;
}t_exe_data;

typedef struct s_redirection{
	int				exit_code;
	t_exe_data		*og_ptr;
	t_tokenchain	*tokenchain;
	int				last_pid;
	int				pipe_read;
	int				pipe_write;
	int				heredoc_num;
}t_redirection;

typedef struct s_expend
{
	int			t;
	int			l;
	int			arg_num;
	int			argv_flag;
	t_exe_data	*exe_ptr;
	t_exe_data	**exe_data;
	int			error;
}t_expend;
//?-----------PROTOTYPES------------?//

int				is_white_space(int a);
int				is_special_char(char a);

void			myerror(char *str);
int				lexer(t_tokenchain *tokenchain, t_redirection *redirection);
t_tokenchain	*tokenchain_create(void);
void			print_token_chain(t_tokenchain *tokenchain);
void			free_str_in_token(t_tokenchain *tokenchain);
int				expander(t_tokenchain *tokenchain, t_env **env_lst, \
t_redirection *redirection);
void			get_token_str(t_token *token, t_env **env_lst, \
char *str, t_redirection *redirection);
int				check_type(t_token *token);
char			*tokenstring(t_token *token, t_env **env_lst, \
t_redirection *redirection);
int				open_outfile(t_exe_data *exe_data, t_token *token, \
t_env **env_lst, t_redirection *redirection);
int				open_outfile_app(t_exe_data *exe_data, t_token *token, \
t_env **env_lst, t_redirection *redirection);
int				open_infile(t_exe_data *exe_data, t_token *token, \
t_env **env_lst, t_redirection *redirection);
int				reset_fd(int *fd);
int				get_here_len(t_token *token, int *expend_flag);
char			*get_here_str(t_token *token, char *str);
int				heredoc_read(char *delimiter, int expend_flag, \
t_exe_data *exe_data, t_env **env_lst, t_redirection *redirection);
int				get_token_length(t_token *token, \
t_env **env_lst, t_redirection *redirection);
int				is_valid_var(char c, int i);
char			*get_value(char *str, t_env **env_lst, \
t_redirection *redirection);
int				strlen_with_check(char *str);
void			found_rediretion(t_tokenchain *tokenchain, t_expend *exp, \
t_redirection 	*redirection, t_env **env_lst, t_exe_data *exe_data);
int				token_to_str(t_expend *exp, t_tokenchain *tokenchain, \
t_redirection *redirection, t_env **env_lst);
void			expander_setup(t_expend *exp, \
t_exe_data **exe_data);
int				add_lst_t_exe_data(t_exe_data **exe_data, t_exe_data **exe_ptr);
void			execution_loop(t_exe_data *exe_data, t_env **env_lst, \
t_redirection *redirection, int *built_in_flag);
int				pipe_start(t_exe_data *exe_data, t_redirection *redirection);
int				close_files_and_pipes(t_exe_data *exe_data, t_redirection *redirection);
void			tokenchain_free(t_tokenchain *tokenchain);
void			free_all_t_exe_data(t_exe_data *ptr);
void			clean_exit(t_redirection *redirection, t_env **env_lst);
int				at_eof(char *str, char *delimiter);

void			changing_fd_in_out(t_exe_data *exe_data);
t_env			*no_env_case(t_env *env_new);

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
t_env			*env_lstnew(char *content);

/**
 * @brief The env_add_back() function adds every new
 * node created to a linked list structure that stores
 * environment variables
 * @param lst 
 * @param new 
 */
void			env_add_back(t_env **env_lst, t_env *new_env);

/**
 * @brief  The ft_getenv_lst() fucntion obtains all names and 
 * values of the environment variable
 * 
 * @param envp
 * @return double pointer to t_env structure
 */
t_env			**ft_getenv_lst(char **envp);

/**
 * @brief The ft_printenv() function prints out the names and
 * values of the variables in the environment
 * 
 * @param env_lst 
 */
void			ft_printenv(t_env *env_lst);

/**
 * @brief Checks if a identifier has the + operator
 * and modifies the name without the +
 * @param name 
 * @return void* 
 */
void	*var_name_ends_with_plus(char *name);

/**
 * @brief  The ft_putenv() function takes an argument of
 * the form ``name=value'' and adds it to the environment
 * list
 * ft_setenv()
 */
void			ft_putenv(t_env *env_lst, char *name, char *value);

/**
 * @brief The find_env_match() function searches for a
 * matching environment variable name in the environment list.
 * @param env_lst 
 * @param name 
 * @return 1 is returned if a match is found,
 * 0 if there is no match
 */
int				find_env_match(t_env *env_lst, char *name);

/**
 * @brief The ft_setenv() function inserts or resets the environment
 * variable name in the current environment list
 * @return 1 if variable is added, otherwise 0
 */
int				ft_setenv(t_env *env_lst, char *new_env);

/**
 * @brief  The ft_unsetenv() function deletes all instances of the
 * variable name pointed to by name from the environment list
 * 
 * @param env_lst 
 * @param name 
 */
void			ft_unsetenv(t_env **env_lst, char *name);

/**
 * @brief The ft_getenv() function obtains the current
 * value of the environment variable whose name is provided
 * 
 * @param env_lst 
 * @param name
 * @return pointer to environment value, otherwise NULL
 */
char			*ft_getenv(t_env *env_lst, char *name);

/**
 * @brief The ft_gen_slice() function helps the ft_slice() function 
 * obtain an array of strings
 */
char			**ft_gen_slice(const char *s, \
char c, char **ptr, int ptr_index);

/**
 * @brief The clean_env frees all dynamically allocated memory used
 * in creating an environment list
 * 
 * @param env_lst 
 */
void			clean_env(t_env **env_lst);

/**
 * @brief The ft_slice() function splits a string at the point of the 
 * first matching character provided as the delimiter
 * @param s string to be sliced
 * @param c delimeter
 */
char			**ft_slice(char const *s, char c);
/**
 * @brief The ft_free() function deallocates memory from a **char
 * @param ptr pointer to be deallocated
 * @return NULL
 */
char			**ft_free(char **ptr);
/**
 * @brief The env_id_isvalid() function checks if a variable
 * has the right name
 * 
 * @param new_env_var 
 * @return  
 */
int				env_id_isvalid(char *new_env_var);

/**
 * @brief The invalid_env_id() function is an env_id_isvalid() helper
 * function that checks if the environment variable to be added has
 * the right naming convention
 * 
 * @param new_env 
 * @return
 */
int				invalid_env_id(char *new_env);

typedef struct s_env_string
{
	char			*name;
	char			*join_equal;
	char			*join_value;
}t_env_string;
/**
 * @brief The env_as_string() function gives a pointer to strings
 * of list of environment variables
 * 
 * @param env_lst 
 * @return char** 
 */
char			**env_as_string(t_env **env_lst);

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
 * @param 
 * @return returns an int defined by enum e_error
 */
int				ft_pwd(void);
/**
 * @brief The ft_echo() function prints arguments passed
 * to it delimited by only a single space followed by a new line.
 * The new line is removed when the option -n is used
 * 
 * @param args 
 * @return returns an int defined by enum e_error
 */
int				ft_echo(char **args);
/**
 * @brief The ft_env() function prints a list of environment variables
 * 
 * @param env_lst 
 * @return returns an int defined by enum e_error
 */
int				ft_env(t_env **env_lst);
/**
 * @brief The ft_export() function adds valid variables to the list
 * of environment variables.
 * If the variable is already in the list, it is updated, else it is added.
 * When NULL is passed as the second argument (new_env) the environment
 * variables list is printed
 * 
 * @param env_lst 
 * @param new_env 
 * @return returns an int defined by enum e_error
 */
int				ft_export(t_env **env_lst, char **new_env);

/**
 * @brief The export_error_mssg() function is an 
 * ft_export() helper function that prints an error message
 * when an invalid arg is used as an identifier
 * 
 * @param new_env 
 */

/**
 * @brief The ft_export_print() function prints the key value pairs of
 * all environment variables
 * 
 * @param env_lst 
 */
void	ft_export_print(t_env *env_lst);

void			export_error_mssg(char *new_env);

/**
 * @brief The valid_last_char() function is
 * an ft_export() helper function that checks if
 * the last character of an identifier is valid
 * 
 * @param new_env 
 * @return int 
 */
int				valid_last_char(char *new_env);

/**
 * @brief The valid_first_char() function is 
 * an ft_export() helper function that checks if
 * the first character of an identifier is valid
 * 
 * @param new_env 
 * @return int 
 */
int				valid_first_char(char *new_env);

/**
 * @brief The ft_unset() function deletes all specified variables from the
 * list of environment variables if it exists
 * 
 * @param env_lst 
 * @param env_name 
 * @return returns an int defined by enum e_error
 */
int				ft_unset(t_env **env_lst, char **env_name);

/**
 * @brief ft_cd() function changes the current directory
 * to the specified directory
 * 
 * @param env_lst 
 * @param path_name 
 * @return returns an int defined by enum e_error
 */
int				ft_cd(t_env **env_lst, char **path_name);
/**
 * @brief The cd_tilde_with_path() is an ft_cd() helper function to move 
 * into a directory in case the tilde (~) sign is used as a prefix.
 * An example is: ~/Documents/myfiles
 * 
 * @param env_lst 
 * @param path_name 
 * @return returns 1 if true, otherwise 0
 */
int				cd_tilde_with_path(t_env *env_lst, char **path_name);
/**
 * @brief The cd_error_mssg() function is an 
 * ft_cd() helper function that prints an error message
 * when the path provided is not valid
 * 
 * @param path_name 
 */
void			cd_error_mssg(char **path_name);
/**
 * @brief The set_old_pwd() function is an ft_cd() helper function
 * that sets the old pwd
 * 
 * @param env_lst 
 * @param pwd 
 */
void			set_old_pwd(t_env *env_lst, char *pwd);
/**
 * @brief The old_pwdis_set() function is 
 * ft_cd() helper function that checks if old pwd is
 * among the environment list upon first initialization of
 * all environment variables
 * @param env_lst 
 * @return returns 1 if true, otherwise 0
 */
int				old_pwdis_set(t_env *env_lst);

/**
 * @brief The ft_exit() function terminates a process
 * by setting the g_signal to 0
 * @param args 
 * @return int 
 */
int				ft_exit(char **args);

/* 
====================================================
                      Path                          
====================================================
 */

typedef struct s_path
{
	char	*paths;
	char	*tmp_path;
	char	*join_fwd_slash;
	char	*new_path;
}t_path;

/**
 * @brief The get_cmd_path() function returns the path
 * of an executable file
 * 
 * @param env_lst 
 * @param cmd 
 * @return returns a pointer to char or NULL if no path was found
 */
char			*get_cmd_path(t_env **env_lst, char *cmd);

/* 
====================================================
                      Executor                     
====================================================
 */

/**
 * @brief The cmd_is_builtin() function checks if the passed
 * argument is a shell builtin
 * 
 * @return 1 if true, otherwise 0
 */
int				cmd_is_builtin(char *cmd);

/**
 * @brief The handle_builtin() function executes the minishell built-ins.
 *
 * 
 * @param cmd minishell built-in to be executed
 * @param args pointer to an array of str passed to the minishell built-in
 * @param env pointer to environment variable node
 * @return returns an int defined by enum e_error
 */
int				handle_builtin(char *cmd, char **args, t_env **env);

/**
 * @brief //! TODO Write this notes
 * 
 */
int				execution(t_exe_data *exe_data, \
t_env **env_lst, t_redirection *redirection);

/**
 * @brief move to the next object of the list. The previous one the be deleted
 * 
 * @param exe_data the start of the current list
 * 
 * @return the next one 
 */
t_exe_data		*next_t_exe_data(t_exe_data *exe_data);

/* 
====================================================
                  Heredoc (Expander)                
====================================================
 */

/**
 * @brief The heredoc() function reads a
 *  input via readline and write it in a open file
 * 
 * @param delimiter 
 * @return fdf of the openfile  
 */
int				heredoc(t_exe_data *exe_data, t_token *token, \
t_env **env_lst, t_redirection *redirection);


/* 
====================================================
                         Signals                    
====================================================
 */

/**
 * @brief The signalhandler_ctrlc() function handles an interrupt signal 
 * triggered by ctrl+c
 * 
 * @param sig 
 */
void			signalhandler_ctrlc(int sig);

void			signalhandler_heredoc(int sig);

/**
 * @brief The signalhandler_ctrlslash() function handles an interrupt signal 
 * triggered by ctrl+\
 * 
 * @param sig 
 */
void			signalhandler_ctrlslash(int sig);

/**
 * @brief The set_signals() function sets the signals SIGINT and SIGQUIT
 * 
 */
void			set_signals(void);

/**
 * @brief The clear_signal() function clears the signal set up by the 
 * set_signal() function
 * 
 */
void			clear_signals(void);

/**
 * @brief The reset_signals() function clears and 
 * sets the SIGINT and SIGQUIT signals to SIG_IGN
 * 
 */
void			reset_signals(void);

#endif
