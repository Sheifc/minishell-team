#include "minishell.h"

void    fill_env_list(t_env **head, char **envp, int *i)
{
    char    *key;
    char    *value;

    while (envp[++(*i)] != NULL)
    {
        get_key_value(envp[*i], &key, &value);
        add(head, key, value);
    }
}

void    init_env(t_shell *data, char **envp)
{
    int i;
    int j;

    i = -1;
    j = -1;
    fill_env_list(&(data->env), envp, &i);
    fill_env_list(&(data->export), envp, &j);
}

void	ft_env(t_env *env)
{
    print_list(env);
    return ;
}
