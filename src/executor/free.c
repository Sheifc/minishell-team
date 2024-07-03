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

void    free_all(t_shell data)
{
    if (data.str_cmd)
        free(data.str_cmd);
    free_env_list(data.env);
    free_env_list(data.export);
    clear_structs(&data.token, &data.cmd);
}
