#include "minishell.h"

void clear_structs(t_token **token, t_cmd **cmd)
{
    t_token *current_token = *token;
    t_cmd *current_cmd = *cmd;
    t_cmd *next_cmd;
    t_token *next_token;

    while (current_token != NULL)
    {
        next_token = current_token->next;
        free(current_token);
        current_token = next_token;
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
