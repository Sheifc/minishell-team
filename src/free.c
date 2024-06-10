#include "minishell.h"

void    free_env_list(t_env *head)
{
    t_env *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
}

void    free_env_node(t_env **node)
{
    free((*node)->key);
    free((*node)->value);
    free(*node);
    *node = NULL;
}
