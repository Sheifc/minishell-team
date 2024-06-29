#include "minishell.h"

void	ft_export(t_shell *data)
{
    t_env   *export;
    t_env   *temp;
    char    *key;
    char    *value;
    int     i;

    i = 1;
    while (i < data->cmd->n_args)
    {
        get_key_value(data->cmd->arg[i++], &key, &value);
        pop(&data->export, key);
        add(&data->export, key, value);
        if (value)
        {
            pop(&data->env, key);
            add(&data->env, key, value);
        }
    }
    if (data->cmd->n_args > 1)
        return ;
    export = data->export;
    while (export->key != NULL && export->next != NULL)
    {
        temp = export;
        while (temp->key && temp->next)
        {
            if (ft_strncmp(temp->key, temp->next->key, ft_strlen(temp->key)+1) > 0)
            {
                ft_swap(&temp->key, &temp->next->key);
                ft_swap(&temp->value, &temp->next->value);
            }
            temp = temp->next;
        }
        export = export->next;
    }
    print_list(data->export);
}

// Refactorización válida

/* void    update_env_vars(t_shell *data)
{
    char    *key;
    char    *value;
    int     i;

    i = 1;
    while (i < data->cmd->n_args)
    {
        get_key_value(data->cmd->arg[i++], &key, &value);
        pop(&data->export, key);
        add(&data->export, key, value);
        if (value)
        {
            pop(&data->env, key);
            add(&data->env, key, value);
        }
    }
}

void    sort_and_print_export(t_shell *data)
{
    t_env   *export;
    t_env   *temp;

    export = data->export;
    while (export->key != NULL && export->next != NULL)
    {
        temp = export;
        while (temp->key && temp->next)
        {
            if (ft_strncmp(temp->key, temp->next->key, ft_strlen(temp->key)+1) > 0)
            {
                ft_swap(&temp->key, &temp->next->key);
                ft_swap(&temp->value, &temp->next->value);
            }
            temp = temp->next;
        }
        export = export->next;
    }
    print_list(data->export);
}

void    ft_export(t_shell *data)
{
    if (data->cmd->n_args > 1)
        update_env_vars(data);
    else
        sort_and_print_export(data);
} */
