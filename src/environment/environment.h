/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:18:08 by bogunlan          #+#    #+#             */
/*   Updated: 2022/12/15 20:23:47 by bogunlan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../include/minishell.h"

// NOTE: Moved all declarations here into mininshell.h

typedef struct	s_env
{
char			*name;
char			*value;
struct s_env	*next;
}					t_env;

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
t_env	*ft_getenv_lst(char **envp);

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
void	ft_setenv(t_env *env_list, char *name, char *value);

/**
 * @brief  The ft_unsetenv() function deletes all instances of the
 * variable name pointed to by name from the environment list
 * 
 * @param env_lst 
 * @param name 
 */
void	ft_unsetenv(t_env *env_lst, char *name);

/**
 * @brief The ft_getenv() function obtains the current
 * value of the environment variable, name.
 * 
 * @param env_lst 
 * @param name 
 */
char	*ft_getenv(t_env *env_lst, char *name);

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_slice(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);