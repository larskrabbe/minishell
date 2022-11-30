#include	"environment.h"

void	ft_unsetenv(t_env *env_lst, char *name)
{
	t_env	*env_curr;
	t_env	*env_prev;

	env_curr = env_lst;
	if (!env_lst || !name)
		return ;
	if (find_env_match(env_curr, name))
	{
		env_prev = env_curr->next;
		free(env_curr);
		env_lst = env_prev;
		return ;
	}
	env_prev = env_curr;
	env_lst = env_prev;
	while (env_curr)
	{
		if (find_env_match(env_curr, name))
		{
			env_prev->next = env_curr->next;
			free(env_curr);
			env_curr = env_prev->next;
			env_prev = env_curr;
		}
		else
		{
			env_prev = env_curr;
			env_curr = env_curr->next;
		}
	}
}