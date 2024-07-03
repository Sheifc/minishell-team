#include "minishell.h"

void	init_struct(t_shell *data, char **envp)
{
	data->token = NULL;
	data->cmd = NULL;
    data->env = NULL;
    data->export = NULL;
    data->str_cmd = NULL;
    data->envp = envp;
    data->path = NULL;
    data->status = 0;
    data->pid = 0;
}
