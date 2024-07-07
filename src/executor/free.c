#include "minishell.h"

void    free_all(t_shell *data)
{
    if (data->str_cmd)
    {
        free(data->str_cmd);
        data->str_cmd = NULL;
    }
    if (data->env)
    {
        free_env_list(data->env);
        data->env = NULL;
    }
    if (data->export)
    {
        free_env_list(data->export);
        data->export = NULL;
    }
    if (data->token)
        free_token_list(&data->token);
    if (data->cmd)
        free_cmd_list(&data->cmd);
}

void clear_structs(t_token **token, t_cmd **cmd)
{
	printf("token: %p, *token: %p\n", token, *token);
    if (token && *token)
        free_token_list(token);
    if (cmd && *cmd)
        free_cmd_list(cmd);
}
