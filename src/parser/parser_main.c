#include "minishell.h"

int only_spaces(char *str_cmd)
{
    int i;

    i = 0;
    while(str_cmd[i])
    {
        if(str_cmd[i] != ' ')
            return(0);
        i++;
    }
    return(1);
}

void clear_structs(t_token **token, t_cmd **cmd)
{
    t_token *current = *token;
    t_cmd *current_cmd = *cmd;
    t_cmd *next_cmd;
    t_token *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    while (current_cmd != NULL)
    {
        if(current_cmd->fdin != -1)
            close(current_cmd->fdin);
        if(current_cmd->fdout != -1)
            close(current_cmd->fdout);
        next_cmd = current_cmd->next;
        free(current_cmd);
        current_cmd = next_cmd;
    }
    *cmd = NULL;
    *token = NULL;
}

void	init_struct(t_shell *data, char **envp)
{
	data->token = NULL;
	data->cmd = NULL;
    data->env = NULL;
    data->export = NULL;
    data->envp = envp;
    data->status = 0;
}
