#include "minishell.h"

void    print_list(t_env *head)
{
    t_env *temp = head;

    while (temp != NULL)
    {
        printf("%s", temp->key);
        if (temp->value)
            printf("=%s", temp->value);
        printf("\n");
        temp = temp->next;
    }
}

void    print_key(t_env *head)
{
    t_env *temp = head;

    while (temp != NULL)
    {
        printf("%s\n", temp->key);
        temp = temp->next;
    }
}

char *print_value(t_env *env, char *key)
{
    while (env)
    {
        if (ft_strncmp(env->key, key, ft_strlen(env->key)+1) == 0)
        {
            return env->value;
        }
        env = env->next;
    }
    return NULL;
}
