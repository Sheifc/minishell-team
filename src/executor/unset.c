#include "minishell.h"

void	ft_unset(t_shell *data)
{
    char *str;
    int i;

    i = 1;
    while (data->cmd->arg[i])
    {
        str = data->cmd->arg[i];
        //printf("env1: %s\n", data->env->key);
        pop(&data->env, str);
        //printf("env1: %s\n", data->env->key);
        pop(&data->export, str);
        i++;
    }
    //print_list(data->env);
}
