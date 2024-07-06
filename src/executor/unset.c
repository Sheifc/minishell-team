#include "minishell.h"

void	ft_unset(t_shell *data)
{
    char *str;
    int i;

    i = 1;
    while (data->cmd->arg[i])
    {
        str = data->cmd->arg[i];
        pop(&data->env, str);
        pop(&data->export, str);
        i++;
    }
}
