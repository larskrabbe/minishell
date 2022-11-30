#include	"environment.h"

t_env	*env_lstnew(char *content)
{
	t_env	*new;
	char	**split;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	split = ft_split(content, '=');
	new->name = split[0];
	new->value = split[1];
	new->next = NULL;
	free(split);
	return (new);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env *curr;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}
