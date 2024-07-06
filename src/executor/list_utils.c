#include "minishell.h"

void    add(t_env **head, char *key, char *value)
{
    t_env *new_node;
    t_env *temp;

    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return(free(key), free(value));
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    if (*head == NULL)
        *head = new_node;
    else
    {
        temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }
}

void    pop(t_env **head, char *key)
{
    t_env   *temp;
    t_env   *prev;
    t_env   *current = *head;

    if (current == NULL)
        return ;
    if (!ft_strncmp(current->key, key, ft_strlen(key) + 1))
    {
        temp = current;
        *head = current->next;
        free_env_node(&temp);
        return ;
    }
    prev = current;
    current = current->next;
    while (current != NULL)
    {
        if (!ft_strncmp(current->key, key, ft_strlen(key) + 1))
        {
            prev->next = current->next;
            free_env_node(&current);
            return ;
        }
        prev = current;
        current = current->next;
    }
}

t_cmd *get_last_cmd(t_cmd *cmd)
{
	t_cmd *aux;

	aux = cmd;
	while (aux->next)
		aux = aux->next;
	return (aux);
}
