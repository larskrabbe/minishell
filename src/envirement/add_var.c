#include	"environment.h"

void	ft_putenv(t_env *env_list, char *name, char *value)
{
	t_env	*env_new;
	char	*content;

	if (!env_list || !name || !value)
		return ;
	content = ft_strjoin(name, "=");
	content = ft_strjoin(content, value);
	env_new = env_lstnew(content);
	env_add_back(&env_list, env_new);
}

void	ft_setenv(t_env *env_lst, char *name, char *value)
{
	t_env	*env_curr;

	env_curr = env_lst;
	if (!env_lst || !name || !value)
		return ;
	while (env_curr)
	{
		if (find_env_match(env_curr, name))
		{
			printf("Match found\n");
			env_curr->value = value;
			return ;
		}
		env_curr = env_curr->next;
	}
	printf("No Match found\n");
	ft_putenv(env_lst, name, value);
}
