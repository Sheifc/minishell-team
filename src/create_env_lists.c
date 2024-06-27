#include "minishell.h"

t_env	*ft_last_parser(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back_parser(t_env **lst, t_env *new)
{
	t_env	*last;

	last = ft_last_parser(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

t_env	*list_empty_parser(char *value, char *key)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->value = ft_strdup(value);
	node->key = ft_strdup(key);
	node->next = NULL;
	return (node);
}

void	create_env_list(char *value, t_env **env, char *key)
{
	t_env	*aux;

	if (!*env)
		*env = list_empty_parser(value, key);
	else
	{
		aux = list_empty_parser(value, key);
		add_back_parser(env, aux);
	}
	free(value);
    free(key);
}
